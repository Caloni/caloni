import frontmatter
from glob import glob


path = "content/posts/*.md"
files = [ glob(path) ]
verbose = False


def transform(operations, files):
  for fname in files:
    if verbose:
      print(fname)
    with open(fname, 'r', encoding='utf8') as f:
      post = frontmatter.load(f)
      for op in operations:
        op(post)
      post_str = frontmatter.dumps(post)
      f.close()
      with open(fname, 'w', encoding='utf8') as f:
        f.write(post_str)


def format():
  def nothing(post):
    pass
  transform([ nothing ], files)


def add_item(post, collection, item):
  if post.get(collection):
    if item not in post[collection]:
      post[collection].append(item)
      return True
  else:
    post[collection] = [ item ]
    return True
  return False


def remove_item(post, collection, item):
  if post.get(collection) and item in post[collection]:
    post[collection].remove(item)
    return True
  return False


def move_category_to_tag(category):
  def func(post):
    if remove_item(post, 'categories', category):
      add_item(post, 'tags', category)
  transform([ func ], files)


def move_tag_to_category(tag):
  def func(post):
    if remove_item(post, 'tags', tag):
      add_item(post, 'categories', tag)
  transform([ func ], files)


def add_tag(tag):
  def func(post):
    add_item(post, 'tags', tag)
  transform([ func ], files)


def add_category(category):
  def func(post):
    add_item(post, 'categories', category)
  transform([ func ], files)


def remove_tag(tag):
  def func(post):
    remove_item(post, 'tags', tag)
  transform([ func ], files)


def remove_category(category):
  def func(post):
    remove_item(post, 'categories', category)
  transform([ func ], files)

