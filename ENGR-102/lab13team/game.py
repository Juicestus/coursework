
tracks = { 'red': set(), 'green': set(), 'yellow': set(), 'blue': set() }

offsets = { 'green': 0, 'yellow': 7, 'blue': 14, 'red': 21 }

def who_is_there(my_color, index):
    for color, offset in offsets.items():
        adj_index = (index + (offsets[my_color] - offsets[color])) % 28
        print(color, adj_index)
        if adj_index in tracks[color]:
            return color
    return None

