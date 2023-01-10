#include "CrippleMD.h"

int parse_md_metadata(FILE *inFile, FILE *outFile, Metadata *metadata){

    char *buffer = calloc(BUFFER_SIZE, sizeof(char));

    read_clean_buffer(inFile, buffer);

    if (strstr(buffer, "---") == NULL){
	return 1;
    }
    if (strstr(buffer, "category: ")  == NULL){
	return 1;
    }
    if (strstr(buffer, "title: ")  == NULL){
	return 1;
    }
    if (strstr(buffer, "date: ")  == NULL){
	return 1;
    }

    char *title = strstr(buffer, "title: ");
    title = title + 7;

    char *category = strstr(buffer, "category: ");
    category = category + 10;

    char *date = strstr(buffer, "date: ");
    date = date + 6;

    char *ptr = strchr(title, '\n');
    *ptr = '\0';
    strncpy(metadata->title, title, 255);

    ptr = strchr(category, '\n');
    *ptr = '\0';
    strncpy(metadata->category, category, 255);

    ptr = strchr(date, '\n');
    *ptr = '\0';

    sscanf(date, "%4d-%2d-%2d", &metadata->year, &metadata->month, &metadata->day);

    char *end = ptr + 5;

    int offset = end - buffer;

    fseek(inFile, offset, SEEK_SET);

    return 0;
}

int parse_md(FILE *inFile, FILE *outFile)
{
	char *buffer = calloc(BUFFER_SIZE, sizeof(char));

	Md_block *tracker_blocks = calloc(sizeof(Md_block), BLOCK_COUNT);
	if (buffer == NULL || tracker_blocks == NULL)
	{
		return 1;
	}

	fill_blocks(tracker_blocks);
	enum block_indexes blocks;

	int elements_read = BUFFER_SIZE;
	char last_char = '\n';

	while (elements_read == BUFFER_SIZE)
	{
		elements_read = read_clean_buffer(inFile, buffer);

		for (int i = 0; i < BUFFER_SIZE; ++i)
		{
			char current_char = buffer[i];

			if (last_char == '\n' && current_char != '#')
			{
				parse_paragraph(tracker_blocks, outFile);
			}

			switch (current_char)
			{
			case '#':
				parse_heading(current_char, last_char, tracker_blocks, outFile);
				break;
			case ' ':
				if (tracker_blocks[heading].level != 0)
				{
					parse_heading(current_char, last_char, tracker_blocks, outFile);
				}
				else
				{
					fprintf(outFile, " ");
				}
				break;
			case '*':
				parse_bold(tracker_blocks, outFile);
				break;
			case '_':
				parse_italic(tracker_blocks, outFile);
				break;
			case '\n':
				end_all_blocks(current_char, last_char, tracker_blocks, outFile);
				break;
			case '\\': // Runs through to default and prints next character
				++i;
			default:
				fprintf(outFile, "%c", buffer[i]);
			}
			last_char = current_char;
		}
	}

	return 0;
}

int read_clean_buffer(FILE *inFile, char *buffer)
{
	int elements_read = fread(buffer, sizeof(char), BUFFER_SIZE, inFile);

	if (*(buffer + BUFFER_SIZE - 1) != ' ' || *(buffer + BUFFER_SIZE - 1) != '\n' && elements_read == BUFFER_SIZE)
	{
		partial_read_cleanup(inFile, buffer);
	}
	if (elements_read != BUFFER_SIZE)
	{ // Jeigu paskutinis bufferis, kad no garbage
		*(buffer + elements_read) = '\0';
	}

	return elements_read;
}

void partial_read_cleanup(FILE *inFile, char *buffer)
{
	int offset;
	if (strrchr(buffer, ' ') > strrchr(buffer, '\n'))
	{ // Suranda paskutini space arba newline
		offset = BUFFER_SIZE - (strrchr(buffer, ' ') - buffer + 1);
	}
	else
	{
		offset = BUFFER_SIZE - (strrchr(buffer, '\n') - buffer + 1);
	}

	*(buffer + BUFFER_SIZE - offset) = '\0'; // Uzbaigia bufferi ties \n arba space
	fseek(inFile, -(offset), SEEK_CUR);		  // Pastumia cursoriu atgal
	return;
}

void parse_bold(Md_block *tracker_blocks, FILE *outFile)
{
	enum block_indexes blocks;

	fprintf(outFile, "%s", tracker_blocks[bold].open == 0 ? tracker_blocks[bold].html_open : tracker_blocks[bold].html_close);
	tracker_blocks[bold].open = !tracker_blocks[bold].open;
}

void parse_italic(Md_block *tracker_blocks, FILE *outFile)
{
	enum block_indexes blocks;

	fprintf(outFile, "%s", tracker_blocks[italic].open == 0 ? tracker_blocks[italic].html_open : tracker_blocks[italic].html_close);
	tracker_blocks[italic].open = !tracker_blocks[italic].open; // Uzdaromas blokas
}

void parse_heading(char current_char, char last_char, Md_block *tracker_blocks, FILE *outFile)
{
	enum block_indexes blocks;

	if (last_char == '\n' || last_char == '#' || tracker_blocks[heading].level != 0)
	{
		tracker_blocks[heading].level += 1;
		if (current_char == ' ')
		{
			tracker_blocks[heading].level -= 1;
			fprintf(outFile, "<h%d>", tracker_blocks[heading].level);
			tracker_blocks[heading].open = 1;

			sprintf(tracker_blocks[heading].html_close, "</h%d>", tracker_blocks[heading].level);
			tracker_blocks[heading].level = 0;
		}
	}
}

void parse_paragraph(Md_block *tracker_blocks, FILE *outFile)
{
	enum block_indexes blocks;

	fprintf(outFile, "%s", tracker_blocks[paragraph].html_open);
	tracker_blocks[paragraph].open = 1;
}

void end_all_blocks(char current_char, char last_char, Md_block *tracker_blocks, FILE *outFile)
{
	enum block_indexes blocks;

	for (int i = 0; i < BLOCK_COUNT; ++i)
	{
		if (tracker_blocks[i].open == 1)
		{
			tracker_blocks[i].open = 0;
			tracker_blocks[i].level = 0;
			fprintf(outFile, "%s", tracker_blocks[i].html_close);
		}
	}

	fprintf(outFile, "\n");
}

void fill_blocks(Md_block *blocks)
{

	enum block_indexes block;

	for (int i = 0; i < 4; ++i)
	{
		blocks[i].open = 0;
		blocks[i].level = 0;
	}
	strncpy(blocks[italic].html_open, "<em>", 6);
	strncpy(blocks[italic].html_close, "</em>", 6);
	strncpy(blocks[bold].html_open, "<b>", 6);
	strncpy(blocks[bold].html_close, "</b>", 6);
	strncpy(blocks[heading].html_open, "<h%d>", 6);
	strncpy(blocks[heading].html_close, "</h%d>", 6);
	strncpy(blocks[paragraph].html_open, "<p>", 6);
	strncpy(blocks[paragraph].html_close, "</p>", 6);
}
