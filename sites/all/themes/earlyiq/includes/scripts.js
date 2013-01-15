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

    /* SSN input validation */
    if($('#field-ssn-add-more-wrapper').length) {
        removeError('#field-ssn-add-more-wrapper input');
        $('#edit-submit').click(function(e) {
            if(ssnCheck('#field-ssn-add-more-wrapper input') != true) {
                e.preventDefault();
            }
        });
    }

    /* toggle script for reports page(s) */
    if($('#main-report-wrapper').length) {
        toggleDetails();
        $('.no-direct').click(function(e) {
            var container = $(this).attr('rel');
            e.preventDefault();
        });

        $('.toggle').click(function() {
            var container = '#' + $(this).attr('rel');
            var theHeight = $(container).height();
            if($(container).hasClass('active')) {
                $(this).parent().removeClass('expand-group');
                $(container).removeClass('active');

            } else {
                $(container).addClass('active');
                $(this).parent().addClass('expand-group');
            }
        });
    }
});

/*
 * Functions
 */

/* prevent default */
function predef(menu) {
    $(menu).click(function(e){
        e.preventDefault();
    });
}

/* ssn valdation realtime error class handling */
function removeError(input) {
    var subj = input, sval;
    $(subj).blur(function() {
        sval = $(subj).val();
        if(!(sval.length < 9) || !(sval.length > 11)) {
            if($(subj).hasClass('error')) {
                $(subj).removeClass('error');
            }
        }
    });
}

/* ssn validation */
function ssnCheck(input) {
    var subj, iVal, val2, wrapper, wrapperContent, eBox;
    $(input).focus(function() {
        $(input).val('');
        if($('#ssn-error-handler').length) {
            if($('#ssn-error-handler').hasClass('error')) {
                alert('1');
                $('#ssn-error-handler').removeClass('error');
            }
        }
    });
    subj = input;
    // if error msg div hasn't been created, create it
    if(!($('#ssn-error-handler').length)) {
        wrapper = $(input).parent().parent().parent('.field-name-field-ssn');
        wrapperContent = $(wrapper).html();
        wrapperContent += '<div id="ssn-error-handler">Format: 666-66-6666 or 666666666</div>';
        $(wrapper).html(wrapperContent);
    }
    iVal = $(subj).val();
    eBox = $('#ssn-error-handler');
    if($(subj).hasClass('error')) $(subj).removeClass('error');
    if($(eBox).hasClass('error')) $(eBox).removeClass('error');
    if(iVal.length > 8 && iVal.length < 12) {
        val2 = iVal.replace(/-/g, "");
        $(subj).val(val2);
        if(val2.length == 9 && $.isNumeric(val2)) {
            $(subj).value == val2;
            return true;
        } else {
            fireError($(subj), $(eBox));
        }
    } else {
        fireError($(subj), $(eBox));
    }
}

/* ssn validation errors */
function fireError(onInput, errorMsg) {
    $(onInput).addClass('error');
    $(errorMsg).addClass('error');
    return false;
}

/* report card details toggle */
function toggleDetails() {
    var container;
    $('.report-details-toggle a').click(function() {
        container = '#' + $(this).attr('rel');
        if($(this).hasClass('show-detail')) {
            $(container).addClass('active');
            $(this).parent().children('.hide-detail').css('display', 'block');
            $(this).parent().children('.show-detail').css('display', 'none');
        } else if ($(this).hasClass('hide-detail')) {
            $(container).removeClass('active');
            $(this).parent().children('.show-detail').css('display', 'block');
            $(this).parent().children('.hide-detail').css('display', 'none');
        }
    });
}