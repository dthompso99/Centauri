(()=>{
	setTimeout(function(){
		console.log('Javascript Engine Loaded 2!');
		setTimeout(function(){
			console.log("setTimeout working!");
		}, 100);
		
		http.get("http://uthertools.thompsoninnovations.com/centauri/mui.js", function(data){
			console.warn(data);
			var f = new Function(data);
			f();
		});
	}, 100);
	return true;
})()