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
            intervalSpeed: 8500,
            slideNumber:1,
            numberShown:1,
            speed:500,
            initFunc:function(){},
          	slideInitFunc:function(){},
      		slideEndFunc:function(){}
        }
        var scroll = new dScroll(constants);
    }

    if($('#block-system-main-menu').length) {
        predef('#block-system-main-menu li a');
    }

});

function predef(menu) {
    $(menu).click(function(e){
        // except for 'about'
        if(!($(this).hasClass('menu-minipanel-1231'))) {
            e.preventDefault();
        }
    });
}