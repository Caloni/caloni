$(function() {
  $("#quick_search").autocomplete({
    source: quick_search_posts,
  });
});

$(document).ready(function(){
  $('#quick_search').focus();
});

$(document).ready(function(){
    $("#quick_search").keypress(function(e){
    if(e.which == 13) {
            window.location = $(this).val();
        }
    });
});
