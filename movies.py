import sys

def print_desc(imdb):
    from imdb import IMDb
    ia = IMDb()
    movie = ia.get_movie(imdb)
    print("desc: \"", movie["title"], ". ", ", ".join(map(str, movie["countries"])), ", ", movie["year"], ". Dirigido por ", ", ".join(map(str, movie["director"])), ", escrito por ", ", ".join(map(str, movie["writer"])), ". Com ", ", ".join(map(str, list(movie["cast"] if "cast" in movie else [])[0:3])), ".\"", sep="")
    print("img: \"", movie["cover url"], "\"", sep="")

if len(sys.argv) < 2:
    print('How to use: python imdb.py imdb')
else:
    print_desc(sys.argv[1])

