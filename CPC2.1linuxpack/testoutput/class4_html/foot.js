


function initializePageNav(iCurrPage)
{
  // var iPageSize;
  //var iProCount  
 
 var b = ((iProCount%iPageSize)!=0);
 var iPageCount = parseInt(iProCount/iPageSize)+(b?1:0);
 if (iCurrPage > iPageCount) return false;
 iCurrPage = parseInt(iCurrPage);
 
 var iPageStart = (iCurrPage-1)*iPageSize+1;
 var iPageEnd = iPageStart+iPageSize-1;
 $("#tContent").load("id"+iPageStart+"-"+iPageEnd+".html #tableContent",function(){drawchart()});
 
 var sTemp = "";
 var sTemp1 = "Items per page:" + iPageSize + "/<span style='color:red'>"+ iProCount +"</span>  Page number:<span style='color:blue'>"+ iCurrPage +"</span>/"+ iPageCount;
 var sTemp2 = "<input type=\"text\" id=\"goPageNo\" value=\""+iCurrPage+"\" size=\"3\" /><input type=\"button\" value=\"GO\" onclick=\"initializePageNav($('#goPageNo').val());\" />"
 if (iProCount==0)
 {
  sTemp = "<font color='#cccccc'>Home Previous Next End</font>";
 }
 else if (iPageCount==1)
 {
  sTemp = "<font color='#cccccc'>Home Previous Next End</font>"
 }
 else if (iPageCount==iCurrPage)
 {
  sTemp = "<a href='Javascript:initializePageNav(1)'>Home</a> <a href='Javascript:initializePageNav("+(iPageCount-1)+")'>Previous</a> <font color='#cccccc'>Next End</font>"
 }
 else if (iCurrPage==1)
 {
  sTemp = "<font color='#cccccc'>Home Previous </font><a href='Javascript:initializePageNav("+(iCurrPage+1)+")'>Next</a> <a href='Javascript:initializePageNav("+iPageCount+")'>End</a>"
 }
 else
 {
  sTemp = "<a href='Javascript:initializePageNav(1)'>Home</a> <a href='Javascript:initializePageNav("+(iCurrPage-1)+")'>Previous</a> <a href='Javascript:initializePageNav("+(iCurrPage+1)+")'>Next</a> <a href='Javascript:initializePageNav("+(iPageCount)+")'>End</a>"
 }
$("#pageDir").html(sTemp +"  "+ sTemp2 + "  " + sTemp1);
  

 CollectGarbage();
}

initializePageNav(1);

