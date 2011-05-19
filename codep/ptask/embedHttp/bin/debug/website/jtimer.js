var updatestate = function(){
    jQuery.getJSON("/status",
        {"name":"mem"},
        function(data) {
            $("#mem").html("total:" + data[0] +
                " <font color=red>used:" + data[1] +
                "M</font>(" + data[2] + "%)");
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
};
var onbrowseclick = function(){
    alert("�˹�����δʵ��");
};

//���������url��/addtask?taskid=***&type=***&name=***&param1=***&&param2=***
var onstartclick = function(){
    var path = $("#inputFile").val();
    if(path.length<=0){
        alert("�������ת���ļ���ַ��");
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
    
    //��ʱ����ҳ��״̬
    setInterval(updatestate,1000); 
});