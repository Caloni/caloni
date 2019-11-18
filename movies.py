import sys

def print_desc(imdb, args):
    castMax = 3 if len(args) == 0 else int(args[0])
    from imdb import IMDb
    ia = IMDb()
    movie = ia.get_movie(imdb)
    originalTitle = '"' + movie["title"] + '"'
    
    def getItem(name, movie, itemMax = 10):
        ret = None
        if name in movie:
            ret = movie[name][0:itemMax]
            ret = str(ret[0]) if len(ret) == 1 else (", ".join(map(str, ret[0:-1])) + " e " + str(ret[-1]))
        return ret

    director = getItem("director", movie)
    writing = getItem("writer", movie)
    casting = getItem("cast", movie, castMax)
    countries = getItem("countries", movie)

    if countries:
        if "year" in movie:
            countries = "(" + countries + ", " + str(movie["year"]) + ")"

    desc = "desc: '" + originalTitle
    if countries:
        desc += " " + countries
    if writing:
        desc += ", escrito por " + writing
    if director:
        desc += ", dirigido por " + director
    if casting:
        desc += ", com " + casting
    desc += ".'"
    print(desc)


if len(sys.argv) < 2:
    print('How to use: python imdb.py imdb')
else:
    print_desc(sys.argv[1], sys.argv[2:])

