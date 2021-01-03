var randomPostIndex = -1;
var randomPost = "/";

function ApplyFilter(filter)
{
    if( filter )
    {
        console.log("search query:", filter);

        $.each( $('.sortable tr:visible'), function() 
        {
            var content = $.trim( $(this).text().replace(/[\t\n]+/g,' ').replace(/  +/g, ' ') );
            var result = content.match(new RegExp(filter, "i"));

            if( result )
            {
                $(this).show();
            }
            else
            {
                $(this).hide();
            }

        });
    }
    else { $.each( $('.sortable tr'), function() { $(this).show(); }); }

    var showing = $('.sortable tr:visible').length;
    randomPostIndex = Math.floor(Math.random() * showing);
    randomPost = $('.sortable tr:visible').eq(randomPostIndex).find('a').prop('href');
    $('#filter').val('');
    $('#filter').attr('placeholder', showing + ' results');
}

function ApplyNotFilter(filter)
{
    if( filter )
    {
        console.log("search query:", filter);

        $.each( $('.sortable tr:visible'), function() 
        {
            var content = $.trim( $(this).text().replace(/[\t\n]+/g,' ').replace(/  +/g, ' ') );
            var result = content.match(new RegExp(filter, "i"));

            if( result )
            {
                $(this).hide();
            }

        });
    }
    else { $.each( $('.sortable tr'), function() { $(this).show(); }); }

    var showing = $('.sortable tr:visible').length;
    randomPostIndex = Math.floor(Math.random() * showing);
    randomPost = $('.sortable tr:visible').eq(randomPostIndex).find('a').prop('href');
    $('#filter').val('');
    $('#filter').attr('placeholder', showing + ' results');
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
        //ApplyFilter(query);
    });
    var query = QueryString['q'];
    $('#filter').val(query);
    $('#filter').focus();
    ApplyFilter(query);
});

$(document).ready(function(){
    $("#filter").keypress(function(e){
    if(e.which == 13) {
            query = $(this).val();
            ApplyFilter(query);
        }
    });
});

