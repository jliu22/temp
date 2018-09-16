'''
flattern json

{'a': 1,
 'c': {'a': 2,
       'b': {'x': 5,
             'y' : 10}},
 'd': [1, 2, 3]}

to

{'a': 1,
 'c_a': 2,
 'c_b_x': 5,
 'c_b_y': 10,
 'd': [1, 2, 3]}
'''

import collections


def flatten(d, parent_key='', sep='_'):

    items = []

    for k, v in d.items():
        new_key = parent_key + sep + k if parent_key else k
        if isinstance(v, collections.MutableMapping):
            items.extend(flatten(v, new_key, sep=sep).items())
        else:
            items.append((new_key, v))

    return dict(items)


# return a list keep the order of key appearance
def flatten2(d, parent_key='', sep='_'):

    items = []

    for k, v in d.items():
        new_key = parent_key + sep + k if parent_key else k

        if isinstance(v, collections.MutableMapping):
            items.extend(flatten(v, new_key, sep=sep).items())

        elif isinstance(v, list):
            dict_items = collections.OrderedDict((str(v.index(va)), va) for va in v)
      	    items.extend(flatten(dict_items, new_key, sep=sep).items())

	else:
            items.append((new_key, v))

    return collections.OrderedDict(items).items()

if __name__== "__main__":
    d = {'a': 1, 'c': {'a': 2, 'b': {'x': 5, 'y' : 10}}, 'd': [1, 2, 3]}
    print d
    print flatten(d)
    print ''

    d = {'a': 1, 'c': {'a': 2, 'b': {'x': 5, 'y' : 10}}, 'd': [{'e' : [1, 2, 3]}, {'f' : 2}, {'g' : 3}]}
    print d
    print flatten(d)
    print flatten2(d)
