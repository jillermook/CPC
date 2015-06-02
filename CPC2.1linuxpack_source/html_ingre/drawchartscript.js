
function drawchart(){
//labelsset
var startnum = Number(document.getElementById("startnum").innerHTML);
for (i = startnum; (i <= (startnum+iPageSize-1))&&(i <= dataarr.length); i++) { 
var ctx = document.getElementById("myChart"+i).getContext("2d");
var linedata = {
	labels : labelsset,
	datasets : [
	
		{
			fillColor : "rgba(151,187,205,0.5)",
			strokeColor : "rgba(151,187,205,1)",
			pointColor : "rgba(151,187,205,1)",
			pointStrokeColor : "#fff",
			data : dataarr[i-1]
		}
	]
};

var myLineChart = new Chart(ctx).Line(linedata,{
					 scaleOverride: true,
					 scaleSteps: 3,
					 scaleStepWidth: 2,
					 scaleStartValue: 0,                    
                     scaleFontFamily : "Microsoft Yahei",                   
                     scaleFontSize : 10,                   
                     scaleFontStyle : "bold",                  
                     scaleFontColor : "#ffa45e",                   
                     scaleLineColor : "blue",                 
                     scaleLineWidth : 1,                   
                     scaleShowGridLines : true,                   
                     scaleGridLineColor : "rgba(0,0,0,.05)",                     
                     animation : true,
                     animationSteps : 60,
                     animationEasing : "easeOutQuart",
         });

    
 }
  }
