(()=>{
	try {
		setTimeout(function(){
			console.log('Javascript Engine Loaded 2!');
			setTimeout(function(){
				console.log("setTimeout working!");
			}, 100);
			
			http.get("http://uthertools.thompsoninnovations.com/centauri/mui.js", function(data){
				console.warn(data);
				var i = ui.createElement('InputBox');
				i.setPosition(0.25, 0.25);
				ui.appendChild(i);
				setTimeout(function(){
					i.setPosition(-0.25, -0.25);
				}, 1000);
				
				var b = ui.createElement('InputBox');
				b.setPosition(-0.75, -0.75);
				b.setSize(0.6, 0.04);
				console.log("after set size", b);
				ui.appendChild(b);
			});
		}, 100);
	} catch(err){
		console.warn("Caught Global Error", err.message);
	}
	return true;
})()