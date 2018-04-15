			var lengthOfNum = 3;
			var answer = "";
			var turns= 1;
			function StartWithZero(str){
				return str.toString().charAt(0) == 0;
			}
			function isNumber( input ) {
 				return isNaN( input );
			}
			
			function check(sizeForm) {
				lengthOfNum = document.getElementById("Choosed").value=sizeForm;
			}
			
			function GetResults( str ){
				var i;
				var bulls = 0;
				var cows = 0;
				var q = "";
				var result = [0,0,0]; // first- True/false for won game, second - bulls , thirth - cows 

				for(i = 0; i < lengthOfNum; i++){
					q = answer.toString().charAt(i);
					//alert(answer + "> "+ q + "- " + str.toString().charAt(i) + "<");
					if(q == str.toString().charAt(i)){
						result[1]++; //bulls++;
					}else if(str.toString().search(q) != -1){
						result[2]++; //cows++;
					}
				}
				
				if(result[1] == lengthOfNum){
					result[0] = 1;
				}else{
					result[0] = 0;
				}
				alert("bulls: " + result[1] + " cows: "+ result[2]);
				return result;
			}
			
			function UserReady(){
				var Table = document.getElementById("ResultsTable").innerHTML;
				var newOne = document.getElementById("UserInput").value;
				if(isNumber(newOne) || StartWithZero(newOne) || IsDuplicate(newOne)){
					document.getElementById("UserInput").value = "Invalid";
					return;
				}
				if(newOne.length != lengthOfNum){
					document.getElementById("UserInput").value ="Lenght should Be " + lengthOfNum;
					return;
				}
				var results = GetResults(newOne);
				if( results[0]){
					
					document.getElementById("ResultsTable").innerHTML = Table + "<br>" +"Turn(" +turns+")"+ newOne + "=> You WIN :) ";	
					document.getElementById("UserInput").value = "";
					Win();
				}else{
					document.getElementById("ResultsTable").innerHTML = Table + "<br>" + "Turn("+turns+") "+ newOne + "=> bulls = " + results[1] + ", cows = " + results[2] ;	
					document.getElementById("UserInput").value = "";
					turns ++;
				}
			}
			
			function Clear(){
				document.getElementById("ResultsTable").innerHTML = "Results:<br>";
				document.getElementById("DebugTable").innerHTML = "Hints: <br>";
			}
			
			function IsDuplicate(str){
				var i = 0;
				for(i = 0; i <= 9; i+= 1){
					if((str.toString().split(i).length-1) >= 2){
						//alert("ops");
						return 1;
					}
				}
				return 0;
			}
			
			function koala() {
				var i = 0;
				var j = 1;
				var b = "";
				turns = 1;
				
				Clear();
				for(i=0;i < lengthOfNum;i++){
					j*=10;
				}
				do{
					answer= Math.floor((Math.random() * j) + 3);
					b = answer.toString().charAt(0);
					document.getElementById("Choosed").innerHTML = "For debugging: " + answer;	
				}while( StartWithZero(answer) || IsDuplicate(answer) == 1 || (''+answer).length != lengthOfNum);
			}
			function Hint(){
				var Table = document.getElementById("DebugTable").innerHTML;				
				var hintPos = 0;
				do{
					hintPos = Math.floor((Math.random() * 10));
				}while (hintPos > lengthOfNum);
				myHint = answer.toString().charAt(hintPos);
				hintPos++;
				hints++;
				document.getElementById("DebugTable").innerHTML = Table + "<br>"+ "Your Hint on possition: " + hintPos + " is < " + myHint + ">" ; 
				
			}
			
			function Win(){
				alert("!!! You Won !!!\nNumber: "+ answer+"\nturns: " +
				turns+"\nUsed hints: 0\nNumber of Lenght: "+ lengthOfNum);
				Clear();
				hints = 0;
				turns = 1;
				answer = "";
			}
			
			function GiveUp(){
				alert("!!! You Lost !!! \nAnswer: "+ answer+"\nturns: " + 
				turns+"\nUsed hints: 0\nNumber Length: "+ lengthOfNum  );
				Clear();
				turns = 1;
				answer = "";
				hints = 0;
			}
