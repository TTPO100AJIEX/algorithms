const types = [ "RANDOM_SMALL", "RANDOM_BIG", "ALMOST_SORTED", "BACKWARDS_SORTED" ];
const groups =
[
    new Array(((300 - 50) / 50 + 1) * types.length).fill(null).map((_, i) => ({ size: (Math.floor(i / types.length) + 1) * 50, type: types[i % types.length] })),
    new Array(((4100 - 100) / 100 + 1) * types.length).fill(null).map((_, i) => ({ size: (Math.floor(i / types.length) + 1) * 100, type: types[i % types.length] }))
];
const algorithms =
[
    "BINARY_INSERTION",
    "BUBBLE_1",
    "BUBBLE_2",
    "BUBBLE",
    "COUNTING",
    "HEAP",
    "INSERTION",
    "MERGE",
    "QUICK",
    "RADIX",
    "SELECTION",
    "SHELL_CIUR",
    "SHELL"
];
const runs = 10;
export { types, groups, algorithms, runs };