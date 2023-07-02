var pumpkin = [
  124, 112, 59, 73, 167, 100, 105, 75, 59, 23, 16, 181, 165, 104, 43, 49, 118,
  71, 112, 169, 43, 53,
];
var pie = 1;

for (var j = 0; j < 100; j++) {
  for (var i = 0; i < pumpkin.length; i++) {
    pumpkin[i] ^= pie;
    pie = ((pie ^ 0xff) + i * 10) & 0xff;
  }
}

txt = pumpkin.map((x) => String.fromCharCode(x)).join("");
console.log(txt);
