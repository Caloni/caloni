var randomPostIndex = -1;
var randomPost = "/";

function ApplyFilter(filter)
{
    query = $.trim(filter); //trim white space
    queryRegex = $.trim(query);
    regex = new RegExp(queryRegex, "i");
    hides = 0;
    shows = 0;

    $.each( $('.sortable'), function(i, sortable) {
        $('tr', sortable).each(function() {
        var srch = $(this).text() + $(this).find('a').prop('title');
        if( srch.search(regex) < 0 )
        {
            $(this).hide()
            hides++;
        }
        else
        {
            $(this).show();
            shows++;
        }
        });
    });

    total = shows + hides;
    var showing = $('.sortable tr:visible').length;
    randomPostIndex = Math.floor(Math.random() * showing);
    randomPost = $('.sortable tr:visible').eq(randomPostIndex).find('a').prop('href');
    $('#results').text(shows + '/' + total);
}

var QueryString = function () {
  // This function is anonymous, is executed immediately and
  // the return value is assigned to QueryString!
  var query_string = {};
  var query = window.location.search.substring(1);
  var vars = query.split("&");
  for (var i=0;i<vars.length;i++) {
    var pair = vars[i].split("=");
        // If first entry with this name
    if (typeof query_string[pair[0]] === "undefined") {
      query_string[pair[0]] = decodeURIComponent(pair[1]);
        // If second entry with this name
    } else if (typeof query_string[pair[0]] === "string") {
      var arr = [ query_string[pair[0]],decodeURIComponent(pair[1]) ];
      query_string[pair[0]] = arr;
        // If third or later entry with this name
    } else {
      query_string[pair[0]].push(decodeURIComponent(pair[1]));
    }
  }
  return query_string;
}();

$(document).ready(function(){
    $("#filter").keyup(function(event){
        query = $(this).val();
        ApplyFilter(query);
    });
    var query = QueryString['q'];
    $('#filter').val(query);
    $('#filter').focus();
    ApplyFilter(query);
});

$(document).ready(function(){
    $("#filter").keypress(function(e){
    if(e.which == 13) {
            window.location = randomPost;
        }
    });
});

