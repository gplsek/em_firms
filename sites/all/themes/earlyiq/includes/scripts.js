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

    /* test for appropriate values in SSN input */
    if($('#edit-name').length) {
        ssnCheck('#edit-name');
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

/* SSN INPUT CHECK */

/* testing on name input for now */
function ssnCheck(input) {
    var iVal, val2;
    // reset value on focus
    $(input).focus(function() {
        $(this).val('');
    });
    $(input).blur(function() {
        iVal = this.value;
        if($(this).hasClass('error')) $(this).removeClass('error');
        if(iVal.length > 8 && iVal.length < 12) {
            val2 = iVal.replace(/-/g, "");
            $(this).val(val2);
            if(val2.length == 9 && $.isNumeric(val2)) {
                $(this).value == val2;
            } else { 
                fireError($(this));
            } 
        } else {
            fireError($(this));
        }
    });
}

function fireError(onInput) {
    $(onInput).val('ex: 111-22-3333');
    $(onInput).addClass('error');
}