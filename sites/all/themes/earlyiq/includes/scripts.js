    /***********************************
*    EarlyIQ Javascript 
*    Developer: TragicMedia
*    Created on: 11/8/12
***********************************/
var $ = jQuery.noConflict();
    
    $(document).ready(function() {

    /* homepage slideshow */
    if($('#block-views-earlyiq-slideshow-block-block').length) {
    	var constants = {
            container:'#block-views-earlyiq-slideshow-block-block .view-content .item-list',
            itemClass:'.views-row',
            pageDots:true,
            interval:true,
            intervalSpeed: 9000,
            slideNumber:1,
            numberShown:1,
            speed:500
        }
        var scroll = new dScroll(constants);
    }

    /* prevent default click on main menu items */
    if($('#block-system-main-menu').length) {
        predef('#block-system-main-menu li a');
    }



    /* toggle script for reports page(s) */
    /* dev version, need to optimize */
    if($('#main-report-wrapper').length) {
        $('.no-direct').click(function(e) {
            var container = $(this).attr('rel');
            alert('Company website will be linked for live report cards');
            e.preventDefault();
        });

        $('.toggle').click(function() {
            var container = '#' + $(this).attr('rel');
            var theHeight = $(container).height();

            // if open
            if($(container).hasClass('active')) {
                $(this).parent().removeClass('expand-group');
                $(container).animate({
                    height: 0
                }, {
                    duration: 500, 
                    complete: function() {
                        $(container).removeClass('active');
                        $(container).height('auto');
                    }
                });
            } else {
            // if closed
                $(container).addClass('active');
                $(container).height('0');
                $(this).parent().addClass('expand-group');
                $(container).animate({
                    height: theHeight
                }, {
                    duration: 500
                });
            }
        });
    }
});

function predef(menu) {
    $(menu).click(function(e){
        e.preventDefault();
    });
}