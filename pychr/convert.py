import png
from itertools import izip_longest

def grouper(n, iterable, padvalue=None):
    "grouper(3, 'abcdefg', 'x') --> ('a','b','c'), ('d','e','f'), ('g','x','x')"
    return izip_longest(*[iter(iterable)]*n, fillvalue=padvalue)

tiles = []

def read_tiles(pngfile):
    r = png.Reader(pngfile)
    pngdata = r.read()
    l = list(pngdata[2])

    for line in xrange(32):
        for i in xrange(16):
            tiles.append([])

        for i in xrange(8):
            tile = line*16
            for j in grouper(8, l[i + line*8]):
                tiles[tile].extend(j)
                tile += 1
                
def print_tile(tile):
    for y in xrange(8):
        print " ".join(map(str, tile[0+y*8:8+y*8]))

def to_byte(bin_array):
    return (128*bin_array[0]
            + 64*bin_array[1]
            + 32*bin_array[2]
            + 16*bin_array[3]
            + 8*bin_array[4]
            + 4*bin_array[5]
            + 2*bin_array[6]
            + 1*bin_array[7])

def convert_tile_to_bytes(tile):
    layer1 = []
    layer2 = []
    for i in xrange(64):
        layer1.append(tile[i] & 1)
        layer2.append(tile[i] & 2)
    layer1.extend(layer2)
    bytes = []
    for bin_array in grouper(8, layer1):
        bytes.append(to_byte(bin_array))
    return bytes

if __name__ == "__main__":
    read_tiles("gfx.png")

    f = open("hero.chr", "w")

    for tile in tiles:
        bytes = convert_tile_to_bytes(tile)
        for byte in bytes:
            f.write(chr(byte))

    f.close()
