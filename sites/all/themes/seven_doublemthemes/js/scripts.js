/***********************************
*    Grace Javascript 
*    Developer: TragicMedia
*    Created on: 11/8/12
***********************************/
var $ = jQuery.noConflict();
$(document).ready(function() {
if($('#block-views-earlyiq-slideshow-block-block').length) {
	var constants = {
        container:'#block-views-earlyiq-slideshow-block-block .view-content .item-list',
        itemClass:'.views-row',
        pageDots:true,
        interval:true,
        slideNumber:1,
        numberShown:1,
        speed:600,
        initFunc:function(){},
      	slideInitFunc:function(){},
  		slideEndFunc:function(){}
    }
    var scroll = new dScroll(constants);
}

});
