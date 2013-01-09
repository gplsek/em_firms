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
    if($('#field-ssn-add-more-wrapper').length) {
        removeError();
        $('#edit-submit').click(function(e) {
            if(ssnCheck('#field-ssn-add-more-wrapper input') != true) {
                e.preventDefault();
            }
        });
    }

    /* toggle script for reports page(s) */
    /* dev version, need to optimize */
    if($('#main-report-wrapper').length) {
        toggleDetails();
        $('.no-direct').click(function(e) {
            var container = $(this).attr('rel');
            //alert('Company website will be linked for live report cards');
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
function removeError(input) {
    $(input).blur(function() {
        if(!($(input).val().length < 9) || !($(input.val().length > 11)) {
            if($(input).hasClass('error')) $(input).removeClass('error');
        }
    });
}

function ssnCheck(input) {
    var subj, iVal, val2;
    // reset value on focus
    $(input).focus(function() {
        $(this).val('');
    });
        subj = input;
        iVal = $(subj).val();
        if($(subj).hasClass('error')) $(subj).removeClass('error');
        
        if(iVal.length > 8 && iVal.length < 12) {
            val2 = iVal.replace(/-/g, "");
            $(subj).val(val2);
            
            if(val2.length == 9 && $.isNumeric(val2)) {
                $(subj).value == val2;
                return true;
            } else { 
                fireError($(subj));
            } 
        } else {
            fireError($(subj));
        }
    //});
}

function fireError(onInput) {
    $(onInput).val('ex: 111-22-3333');
    $(onInput).addClass('error');
    return false;
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