/**
 * 3장 Test 16
 * 
 * 함수가 결과값으로 리턴됨
 */

function add(a, b, callback) {
	var results = a + b;
    var result22 = a;
	callback(results, result22);

	var history = function() {
		return a + ' + ' + b + ' = ' + results; 
	};
	return history;
}

var ahistory = add(10, 10, function(result, result2) {
	console.log('파라미터로 전달된 콜백 함수 호출됨.');
	console.log('더하기 (10, 10)의 결과 : %d %d', result, result2);
});

console.log('결과값으로 받은 함수 실행 결과 : ' + ahistory());

