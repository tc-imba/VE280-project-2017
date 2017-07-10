import random
import math

terrains = [
    "PPPPPPPPPPPPPPPPPPPP",
    "PHPHPHHPHPHLLLLLHHHP",
    "PPPFPHHFLLLFPPPPPPPP",
    "PFPFPHHFLFHFLLHFPPPP",
    "PFPPPHHLLFHHHLHFFHHP",
    "PHPLLLPPPPPPFFFPPFPP",
    "PHPLLLLLLLLLLLFPFFPP",
    "PHPLLLPPPPPPFFFFPPPP",
    "PHFPPPPHPFHPPPPFHHHP",
    "PHPHFHFHPFLLLLFFPPPP",
    "PFHHPPFFHPPFFFPPPPPP",
    "PFFHHHPPPPPFFLLLLLLP",
    "PHHHHHHHHHHHHHHHHHHP",
    "PPPPPPPPPPPPPPPPPPPP",
    "PLLLLFPFFPPPPFFFPPPP",
    "PFFHHFPFPLLLLPFFPPPP",
    "PFHHHFPPLLLLLLPFPPPP",
    "PHFHPPFFPLLLLPFFPPPP",
    "PHPPFPPFFPPPPFFFPPPP",
    "PPPPPPPPPPPPPPPPPPPP",
]

terrains = ''.join(terrains)

creatures = [
    "flytrap",
    "food",
    "hop",
    "lrover",
    "rrover",
    "alt_rover",
    "landmine",
]

directions = ["east", "west", "south", "north"]

blocks = [i for i in range(400)]

for i in range(400):
    a = random.randint(0, 399)
    b = random.randint(0, 399)
    blocks[a], blocks[b] = blocks[b], blocks[a]

# print(blocks)

for i in range(50):
    x = math.floor(blocks[i] / 20)
    y = blocks[i] % 20
    c = random.randint(0, len(creatures) - 1)
    d = random.randint(0, len(directions) - 1)
    a1 = random.randint(0, 4)
    a2 = random.randint(0, 4)
    s = ""
    if terrains[blocks[i]] == 'L':
        s += "f "
    else:
        s += a1 == 0 and "f " or ""
    s += a2 == 0 and "a " or ""
    print(creatures[c], directions[d], x, y, s)
