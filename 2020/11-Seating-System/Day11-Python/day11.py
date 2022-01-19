# advent of code 2021, day 11
# michel billaud

from copy import deepcopy

deltas = [(-1, -1), (-1, 0), (-1, 1),
          (0, -1),           (0, 1),
          (1, -1),  (1, 0), (1, 1)]

def translate(p, v):
    return (p[0] + v[0], p[1] + v[1])

class Grid:
    def __init__(self, data):
        self.data = deepcopy(data)
        self.nr = len(data)
        self.nc = len(data[0])
        self.dims = (self.nr, self.nc)

    def contains(self, point):
        (r, c) = point
        if r < 0 or c < 0:
            return False
        return r < self.nr and c < self.nc

    def neighbours(self, point):
        v = [translate(point, d) for d in deltas]
        return [p for p in v if self.contains(p)]

    def eachPosition(self):
        for r in range(self.nr):
            for c in range(self.nc):
                yield (r, c)

    def isOccupied(self, p):
        (r, c) = p
        return self.data[r][c] == "#"

    def isFree(self, p):
        (r, c) = p
        return self.data[r][c] == "L"

    def pointsOfRow(self, r):
        return [(r, c) for c in range(self.nc)]

    def nextOccupied(self, p):
        occ = [n for n in self.neighbours(p) if self.isOccupied(n)]
        return len(occ)

    def nbOccupied(self):
        return sum(
            [1 for p in self.eachPosition() if self.isOccupied(p)]
        )

    def newStatePart1(self, p):
        nb = self.nextOccupied(p)
        (r, c) = p
        state = self.data[r][c]
        if state == "L" and nb == 0:
            return "#"
        if state == "#" and nb >= 4:
            return "L"
        return state

    def visibleAlongDirection(self, p, d):
        v = translate(p, d)
        if not self.contains(v) or self.isFree(v):
            return 0
        if self.isOccupied(v):
            return 1
        return self.visibleAlongDirection(v, d)

    def visibleOccupied(self, p):   # TODO
        return sum([self.visibleAlongDirection(p, d) for d in deltas])

    def newStatePart2(self, p):
        nb = self.visibleOccupied(p)
        (r, c) = p
        state = self.data[r][c]
        if state == "L" and nb == 0:
            return "#"
        if state == "#" and nb >= 5:
            return "L"
        return state
    
    # evo : pour une grille et une position, donne l'état suivant
    def next(self, nextState):
        return Grid([
            [nextState(self, p) for p in self.pointsOfRow(r)]
            for r in range(self.nr)]
        )
       
    def differences(self, other):
        return [(r, c) for (r, c) in self.eachPosition()
                if self.data[r][c] != other.data[r][c]]

    def print(self):
        for row in self.data:
            print(" ".join(row))
        print(" ")


class Puzzle:
    def __init__(self, filename):
        self.filename = filename
        f = open(filename, "r")
        self.grid = Grid([list(line) for line in f.read().splitlines()])

    def solve(self, evo):
        current = self.grid
        while True:
            next = current.next(evo)
            n = len(current.differences(next))
            if n == 0:
                break
            current = next
        return next.nbOccupied()
  
    def part1(self):
        nb = self.solve(lambda g, p: g.newStatePart1(p))
        print("# Part 1 ", self.filename, ":",
              nb, "seats occupied")

    def part2(self):
        nb = self.solve(lambda g, p: g.newStatePart2(p))
        print("# Part 2 ", self.filename, ":",
              nb, "seats occupied")

# --------------------------------------------------------------


small = Puzzle("../small.txt")
small.part1()
small.part2()

large = Puzzle("../large.txt")
large.part1()
large.part2()
