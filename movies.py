import sys

def print_desc(imdb):
    from imdb import IMDb
    ia = IMDb()
    movie = ia.get_movie(imdb)
    originalTitle = '"' + movie["title"] + '"'
    countriesYear = "(" + ", ".join(map(str, movie["countries"])) + ", " + str(movie["year"]) + ")"
    writing = movie["writer"]
    writing = str(writing[0]) if len(writing) == 1 else (", ".join(map(str, writing[0:-1])) + " e " + str(writing[-1]))
    director = movie["director"]
    director = str(director[0]) if len(director) == 1 else (", ".join(map(str, director[0:-1])) + " e " + str(director[-1]))
    casting = movie["cast"][0:3]
    casting = str(casting[0]) if len(casting) == 1 else (", ".join(map(str, casting[0:-1])) + " e " + str(casting[-1]))
    desc = "desc: '" + originalTitle + " " + countriesYear + ", escrito por " + writing + ", dirigido por " + director + ", com " + casting + ".'"
    print(desc)

if len(sys.argv) < 2:
    print('How to use: python imdb.py imdb')
else:
    print_desc(sys.argv[1])

