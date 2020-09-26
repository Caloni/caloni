#
# This script get information from IMDB and write to a data file or print
# a summary from the movie/series used as a template publication.
#
# author Wanderley Caloni <wanderley.caloni@gmail.com>
# date 2020-06
#
import sys
from imdb import IMDb

def print_desc(imdb, args):
    castMax = 3 if len(args) == 0 else int(args[0])
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

    desc = originalTitle
    if countries:
        desc += " " + countries
    if writing:
        desc += ", escrito por " + writing
    if director:
        desc += ", dirigido por " + director
    if casting:
        desc += ", com " + casting
    desc += "."
    print(desc)


def save_database(imdb, path):
    ignore_keys = [ 'synopsis', 'plot', 'writer', 'director', 'miscellaneous' ]
    f = open(path, 'w', encoding='utf8')
    ia = IMDb()
    movie = ia.get_movie(imdb)
    f.write('[imdb]\n"id" = "' + imdb + '"\n')
    for k, v in movie.iteritems():
        if k not in ignore_keys:
            if type(v) == type([]):
                items = map(lambda s: '"' + str(s).replace('"', "'") + '"', v[0:6])
                items = list(dict.fromkeys(items))
                items = [i for i in items if i and i != '""'] 
                v = ", ".join(items)
                f.write('"' + k + '" = [ ' + str(v) + ' ]\n')
            else:
                f.write('"' + k + '" = "' + str(v).replace('"', "'") + '"\n')


def search_movie(query):
    ia = IMDb()
    movies = ia.search_movie(query)
    results = []
    for m in movies[0:5]:
        plot = ia.get_movie_plot(m.movieID)
        if 'plot' in plot['data']:
            plot = plot['data']['plot'][0][0:140]
        else:
            plot = 'This is a Michael Bay plot.'
        results.append({ 'id': str(m.movieID), 'title': str(m), 'plot': plot})
    for r in results:
        print(r)
    opt = input('what is the movie? ')
    return results[int(opt)]['id']


if len(sys.argv) < 2:
    print("""How to use:
    python movies.py cinemaqui imdb-id [cast-max]
    python movies.py search file-slug path-to-save
    python movies.py imdb-id path-to-save
    """
    )
else:
    if sys.argv[1] == 'cinemaqui':
        print_desc(sys.argv[2], sys.argv[3:])
    elif sys.argv[1] == 'search':
        imdb = search_movie(sys.argv[2].replace('-', ' '))
        save_database(imdb, sys.argv[3])
    else:
        save_database(sys.argv[1], sys.argv[2])

