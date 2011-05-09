var OnTimer = function(){

jQuery.getJSON("/status",
		{"name":"mem"},
		function(data) {
            $("#mem").html("total:" + data[0] +
                " <font color=red>used:" + data[1] +
                "</font>(" + data[2] + "%)");
        });
}
$(document).ready(function(){
    
    setInterval("OnTimer();",1000); 
    $("#btnBrowse").click(function(){
    alert("eh");
    });
});