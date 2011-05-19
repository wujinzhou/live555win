var updatestate = function(){
    jQuery.getJSON("/taskstatus",
        {},
        function(data) {
            var strData ="";
            for(var i=0;i<data.length;i++){
                strData += "<div>id:" + data[i][0] +
                    " type:" + data[i][1] +
                    " path:" + data[i][2] + "</div>";
            }
            $("#div_task").html(strData)
        });
    
    jQuery.getJSON("/getstatus",
        {},
        function(data) {
            var tasks = "";
            for(var i=0;i<data.length;i++){
                tasks = "<p>" + data[i][0] + " " + data[i][1] + " " + data[i][2] + " " + data[i][3] + "</p>";
            }
            $("#div_task").html(tasks);
        });
        
    jQuery.getJSON("/serverstatus",
        {"name":"mem"},
        function(data) {
            $("#mem").html("total:" + data[0] +
                " <font color=red>used:" + data[1] +
                "M</font>(" + data[2] + "%)");
        });
};
var onbrowseclick = function(){
    alert("此功能暂未实现");
};

var onsetmainnode = function(){
    var path = $("#inputMainNode").val();
    if(path.length<=0){
        alert("请输入主节点地址。");
        return;
    }
    jQuery.getJSON("/setmainnode",
        {"path":path},
        function(data) {
            if("succeed"==data[0]){
                alert("设置成功！");
            }
            else{
                alert(data[1]);
            }
        });
}

//启动任务的url是/addtask?taskid=***&type=***&name=***&param1=***&&param2=***
var onstartclick = function(){
    var path = $("#inputFile").val();
    if(path.length<=0){
        alert("请输入待转码文件地址。");
        return;
    }
    jQuery.getJSON("/addtask",
        {"taskid":0,
        "type":"hash",
        "name":path,
        "param1":path,
        "param2":0
        },
        function(data) {
            $("#span_res").html(data[3]);
        });
}
$(document).ready(function(){
    $("#btnBrowse").click(onbrowseclick);
    $("#btnStart").click(onstartclick);
    $("#btnSetMainNode").click(onsetmainnode);
    
    //定时更新页面状态
    setInterval(updatestate,1000); 
});