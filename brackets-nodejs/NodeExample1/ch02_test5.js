var calct = require('./calc');
console.log('모듈로 분리한 후 - calct.add : %d', calct.add(10,10));

var calc2 = require('./calc2');
console.log('모듈로 분리한 후 2 - calc : %d', calc2.add(10,10));