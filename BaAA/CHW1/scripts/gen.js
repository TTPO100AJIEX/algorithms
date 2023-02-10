import { groups } from "./config.js";
const data_small = new Array(5000).fill(null).map(e => Math.floor(Math.random() * 5));
const data_big = new Array(5000).fill(null).map(e => Math.floor(Math.random() * 4000));

import fs from 'fs';
for (let groupIndex = 0; groupIndex < groups.length; groupIndex++)
{
    if (fs.existsSync(`tests/group${groupIndex + 1}`)) fs.rmSync(`tests/group${groupIndex + 1}`, { recursive: true });
    const group = groups[groupIndex];
    for (let testIndex = 0; testIndex < group.length; testIndex++)
    {
        const test = group[testIndex], { input, output } = generateTest(test.size, test.type);
        fs.mkdirSync(`tests/group${groupIndex + 1}/test${testIndex + 1}`, { recursive: true });
        fs.writeFileSync(`tests/group${groupIndex + 1}/test${testIndex + 1}/in.in`, input, "utf-8");
        fs.writeFileSync(`tests/group${groupIndex + 1}/test${testIndex + 1}/out.out`, output, "utf-8");
        fs.writeFileSync(`tests/group${groupIndex + 1}/test${testIndex + 1}/descirption.txt`, `${test.size} ${test.type}`, "utf-8");
    }
}

function generateTest(size, type)
{
    let arr = [ ];
    switch (type)
    {
        case "RANDOM_SMALL": { arr = data_small.slice(0, size); break; }
        case "RANDOM_BIG": { arr = data_big.slice(0, size); break; }
        case "ALMOST_SORTED":
        {
            arr = new Array(size).fill(null).map((_, i) => i + 1);
            for (let i = 0; i < size / 8; i++)
            {
                let ind1 = Math.floor(Math.random() * arr.length), ind2 = Math.floor(Math.random() * arr.length);
                [ arr[ind1], arr[ind2] ] = [ arr[ind2], arr[ind1] ];
            }
            break;
        }
        case "BACKWARDS_SORTED": { arr = new Array(size).fill(null).map((_, i) => i + 1).reverse(); break; }
        default: console.error(`Unknown generateTest type ${type}!`);
    }
    return {
        input: `${size}\n` + arr.join(' '),
        output: arr.sort((a, b) => a - b).join(' ')
    };
}