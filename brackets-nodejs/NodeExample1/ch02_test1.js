var result = 0;

console.time('duration_sum');
for(var i = 1; i<=1000;i++) result += i;

console.timeEnd('duration_sum');
console.log('result : %d',result);

console.log('file name : %s',__filename);
console.log('file pass : %s',__dirname);

var Person = {name:"소녀시대", age:20};
console.dir(Person);