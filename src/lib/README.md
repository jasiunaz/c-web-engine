C module that converts limited md files into html code

Supported functions:

Headers:
```md
# Title ; Converts text into <h1>Title</h1>
## Title ; Converts text into <h2>Title</h2>
###### Title ; Converts text into <h6>Title</h6>
```

Paragraphs:
```md
Lorem ipsum darbas nuo 23.30 efektyviausias ; Converts text into <p> Text </p>
```

Bold and Italic fonts:
```md
Aš mėgstu kates ir *pieną* haha ; Converts into <p> Aš mėgstu kates ir <b>pieną</b> haha </p>
Aš mėgstu _kates_ ir pieną haha ; Converts into <p> Aš mėgstu <em>kates</em> ir pieną haha </p>
Aš mėgstu kates _*ir*_ pieną haha ; Converts into <p> Aš mėgstu <em><b>ir</b></em> pieną haha </p>
```
