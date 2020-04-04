console.log('argv 속성의 파라미터 수 : ' + process.argv.length);
//console.dir(process.argv);

process.argv.forEach(function(item, index) {
    console.log(index + ' : ',item);
})

var nconf = require('nconf');
nconf.env();

//console.log('OS 환경 변수 : ', process.env[OS]);
console.log('OS 환경 변수의 값 : %s', nconf.get('OS'));