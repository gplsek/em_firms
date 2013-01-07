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
    /*if($('#edit-name').length) {
        ssnCheck('#edit-name');
    }*/

    /* toggle script for reports page(s) */
    /* dev version, need to optimize */
    if($('#main-report-wrapper').length) {
        toggleDetails();
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
                $(container).removeClass('active');
            
            } else {
            // if closed
                $(container).addClass('active');
                $(this).parent().addClass('expand-group');
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

/* basic function for showing/hiding report list item details */
function toggleDetails() {
    var container;
    $('.report-details-toggle a').click(function() {
        container = '#' + $(this).attr('rel');
        if($(this).hasClass('show-detail')) {
//            $(container).css('display', 'block');
            $(container).addClass('active');
            $(this).parent().children('.hide-detail').css('display', 'block');
            $(this).parent().children('.show-detail').css('display', 'none');
        } else if ($(this).hasClass('hide-detail')) {
//            $(container).css('display', 'none');
            $(container).removeClass('active');
            $(this).parent().children('.show-detail').css('display', 'block');
            $(this).parent().children('.hide-detail').css('display', 'none');
        }
    });
}