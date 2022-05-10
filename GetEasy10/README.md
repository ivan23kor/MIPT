# GetEasy10

_(TODO list for developers is at the bottom)_

## [Intro](https://www.youtube.com/watch?v=WOIFQCOeso4)

_Experiencing lotta stress during exams?_

_Tired of inequality in the world of academia?_

_Wanna chill instead of homework?_

__We have designed this App to solve the aforementioned problems__

## Idea in a nutshell

Basically, the App consists of three main parts:

1. [Image parser](#image-parser)
2. [Server](#other-section)
3. [Solver](#other-section)

### Image parser
This part is in charge of making text out of an image using the [ABBYY's API](https://www.abbyy.com/en-us/cloud-ocr-sdk/).
The API provides anyone with 50 free recognitions upon account creation.

As ABBYY's software is still not perfect, a lot of hard-coded heuristics have been implemented (and many are yet to come).

Developer(-s): __Ivan Korostelev__, __Pavel Fedosov__


### Server
The server is the core idea behind the App's reliability.
After the parser had done its part of the job, the parsed problems are then headed to the user via email for a double-check.
Additionally, the server serves as a barrier for not letting anyone but students employ the app.

To comply with the professors' wishes, some cryptography patterns may be embedded into the server just for showing off.

Developer(-s): __Ivan Korostelev__


### Solver
The solver is the heart of the project. While [OCR](https://en.wikipedia.org/wiki/Optical_character_recognition) and email conversation are important, the app exists to solve the exam.
With an accurate problem-solving engine and a comprehensive step-by-step solution output, this part delivers __100%__ performance at the exam.

Developer(-s): __Pavel Fedosov__, __Artem Torlak__, __Genrikh Kenigsberger__


## TODO

_(Ranked in the order of importance)_

**One known bug is in parser (wrong arguments order in problem11) and some of the bugs are in problem solvers**
[ ] __All:__ Testing

+ The program has been tested on the first OCR run results.
+ For now, I have 49 pages. Anyone who registers with an email gets 50 pages for free.

[x] __Server:__ Send email for double-checking

[x] __Server:__ Receive email from double-checking

[x] __Parser:__ Double-checking results parsing

[x] __Other:__ Test in a real exam environment

[ ] __README:__ Add deployment examples
