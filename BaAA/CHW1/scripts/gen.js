let sizes = [ ];
for (let i = 50; i <= 300; i += 50) sizes.push(i);
for (let i = 100; i <= 4100; i += 100) sizes.push(i);
sizes = [ ...new Set(sizes) ];

const types = [ "RANDOM_SMALL", "RANDOM_BIG", "ALMOST_SORTED", "BACKWARDS_SORTED" ];

import fs from 'fs';
for (let i = 0; i < sizes.length; i++)
{
    for (let j = 0; j < types.length; j++)
    {
        const { test, answer } = generateTest(sizes[i], types[j]);
        fs.mkdirSync(`tests/${sizes[i]}-${types[j]}`);
        fs.writeFileSync(`tests/${sizes[i]}-${types[j]}/in.in`, test, "utf-8");
        fs.writeFileSync(`tests/${sizes[i]}-${types[j]}/out.out`, answer, "utf-8");
    }
}

function generateTest(size, type)
{
    let arr = [ ];
    switch (type)
    {
        case "RANDOM_SMALL": { arr = new Array(size).fill(null).map(e => Math.floor(Math.random() * 5)); break; }
        case "RANDOM_BIG": { arr = new Array(size).fill(null).map(e => Math.floor(Math.random() * 4000)); break; }
        case "ALMOST_SORTED":
        {
            arr = new Array(size).fill(null).map((_, i) => i + 1);
            for (let i = 0; i < size / 25; i++)
            {
                let swap = Math.floor(Math.random() * (arr.length - 1));
                [ arr[swap], arr[swap + 1] ] = [ arr[swap + 1], arr[swap] ];
            }
            break;
        }
        case "BACKWARDS_SORTED": { arr = new Array(size).fill(null).map((_, i) => i + 1).reverse(); break; }
        default: console.error(`Unknown generateTest type ${type}!`);
    }
    return {
        test: arr.join(' '),
        answer: arr.sort().join(' ')
    };
}