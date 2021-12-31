
deltas = [(-1, -1), (-1, 0), (-1, 1),
         (0, -1),           (0, 1),
        (1, -1),  (1, 0), (1, 1)]

def translate(p, v):
    return (p[0] +v [0], p[1] + v[1])

def inside(p, dims):
    (r,c) = p
    if r < 0 or c < 0: return False
    (nr, nc) = dims
    return r < nr and c < nc

def neighbours(p, dims):
    v = [ translate(p,d) for d in deltas ]
    return [ p for p in v if inside(p, dims) ]

def eachPosition(dims):
    for r in range(dims[0]):
        for c in range(dims[1]):
            yield (r, c)

def pointsOfRow(r, dims):
    return [ (r, c) for c in range(dims[1])]
            
def nextOccupied(p, grid, dims):
    occ = [ n for n in neighbours(p, dims) if grid[n[0]][n[1]] == "#" ]
    return len(occ)

def next(state, nb):
    if state == "L" and nb == 0 :
        return "#"
    if state == "#" and nb >= 4 :
        return "L"
    return state

def nbOccupied(grid, dims):
    return sum( 
        [ len ([ x for x in row if x == "#" ]) 
         for row in grid ] )

def part1 (filename):
    f = open(filename, "r")
    grid = [ list(line) for line in f.read().splitlines()]
    dims = (len(grid), len(grid))

    changes = -1;
    while changes != 0:
        nb = [ [ nextOccupied( (r,c), grid, dims) for c in range(dims[1]) ]
                for r in range(dims[0])]

        nextGrid = [[ next(grid[r][c], nb[r][c])  for c in range(dims[1]) ]
                for r in range(dims[0])]

        changes = sum( [ 1 for (r, c) in eachPosition(dims) if nextGrid[r][c] != grid[r][c]])
        print ("--", changes, " changements")
        print(nb)
        for row in nextGrid:
            print(str (row))
    
        grid = nextGrid
        
    print ("# Part1 ",filename, ":" , nbOccupied(grid, dims), " seats occupied.")
    
part1 ("../small.txt")
part1 ("../large.txt")

