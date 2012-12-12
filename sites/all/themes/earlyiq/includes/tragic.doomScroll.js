/* Begin: TragicMedia.com - JQuery
/* updated 4/10 by Rich Rudzinski
/*------------------------------------------*/
//var constants = {container:'', btnLeft:'', btnRight:'', itemClass:'', pageDots:bool, interval:bool, intervalSpeed:#, slideNumber:#, numberShown:#, speed:#, initFunc:function(){}, slideInitFunc:function(){}, slideEndFunc:function(){}};
//var scroll = new dScroll(constants);
//Notes: speed works by duration, the larger the number, the slower the slide.

function dScroll(constants) {
	var obj, img;
	this.container = $(constants.container);
	this.containerId = constants.container;
	this.frame = this.container.parent();
	// hide frame to reduce content bouncing
	this.frame.css({'position':'relative', 'opacity':0});
	this.itemClass = constants.itemClass;
	this.slideItems = $(constants.container + ' ' + constants.itemClass);
	this.btnLeft = (constants.btnLeft == '' || constants.btnLeft == undefined) ? false : $(constants.btnLeft);
	this.btnRight = (constants.btnRight == '' || constants.btnRight == undefined) ? false : $(constants.btnRight);
	this.slideNumber = (constants.slideNumber == undefined) ? this.slideNumber = 1 : this.slideNumber = constants.slideNumber;
	this.currSlide = this.slideNumber;
	//this.currSpeed = (this.currSlide == 1) ? 1 : this.currSlide/2;
	this.dir = 'right';
	this.numberShown = (constants.numberShown == undefined) ? this.numberShown = this.slideNumber : this.numberShown = constants.numberShown;
	this.speed = (constants.speed == undefined) ? this.speed = 3000 : this.speed = constants.speed;
	this.pageDots = (constants.pageDots == undefined) ? false : constants.pageDots;
	this.interval = (constants.interval == undefined) ? false : constants.interval;
	this.intervalSpeed = (constants.intervalSpeed == undefined) ? 5000 : constants.intervalSpeed;
	this.initFunc = (constants.initFunc == undefined) ? false : constants.initFunc;
	this.slideInitFunc = (constants.slideInitFunc == undefined) ? false : constants.slideInitFunc;
	this.slideEndFunc = (constants.slideEndFunc == undefined) ? false : constants.slideEndFunc;
	if(this.slideItems.length%this.numberShown != 0) this.addNodes(this.slideNumber - this.slideItems.length%this.numberShown);
	if(this.slideItems.find('img').length) {
		obj = this;
		img = this.slideItems.find('img')[0];
		if(img.complete || img.readyState === 4) {
			obj.initScroll();
		} else {
			$(img).load(function(){
				obj.initScroll();
			});
		}
		// IE fix
		img.src = this.slideItems.find('img')[0].src;
	} else {
		this.initScroll();
	}
};
// initialize scroller
dScroll.prototype.initScroll = function() {
	this.itemWidth = this.slideItems.width();
	this.itemHeight = this.slideItems.height();
	this.totalItemHeight = this.slideItems.outerHeight(true);
	this.totalItemWidth = this.slideItems.outerWidth(true);
	this.totalWidth = this.totalItemWidth * this.slideItems.length;
	this.totalSlide = this.slideNumber * this.totalItemWidth;
	this.container.left = 0;
	if(this.pageDots && this.slideItems.length > this.numberShown && !($('.page-dots').length)) this.makePageDots();
	this.animate = false;
	this.disabled = false;
	this.createScroll();
};
// add nodes to slideItems when not enough elements for pages
dScroll.prototype.addNodes = function(number) {
	var tempNode;
	for(i=0; i<number; i++) {
		tempNode = this.slideItems[this.slideItems.length-1].cloneNode(false);
		this.container.append(tempNode);
	}
	this.slideItems = $(this.containerId + ' ' + this.itemClass);
};
// Set start position and adjust css for container and frame
dScroll.prototype.createScroll =  function() {
	var frameWidth = this.totalItemWidth * this.numberShown - parseInt($(this.slideItems[0]).css('margin-right'));
	this.container.css({
		//'width': this.totalWidth + 'px',
		'position': 'absolute',
		'left': this.container.left + 'px'});
	this.frame.css({
		//'width': frameWidth + 'px',
		'position':'relative',
		'overflow': 'hidden'});
	this.slideItems.css({
		//'width': this.itemWidth + 'px',
		'float': 'left'});
	this.addBtnEvent();	// add arrow events
	if(this.initFunc) this.initFunc();
	if(this.interval && !this.disabled) this.createInterval(); // create slide interval
};
// add click event
dScroll.prototype.addBtnEvent = function() {
	var obj = this;
	var temp;
	if(this.slideItems.length <= this.numberShown) {
		this.disabled = true;
		if(this.btnLeft) this.btnLeft.addClass('disabled-btn');
		if(this.btnRight) this.btnRight.addClass('disabled-btn');
	} else {
		if(this.btnLeft) {
			this.btnLeft.click(function() {
				if(!obj.animate && !obj.disabled) {
					if(obj.scrollInterval) clearInterval(obj.scrollInterval);
					obj.animate = true;
					obj.dir = 'left';
					obj.shiftElementsLeft(obj.slideNumber);
					obj.slideLeft();
				}
				return false;
			});
		}
		if(this.btnRight) {
			this.btnRight.click(function() {
				if(!obj.animate && !obj.disabled) {
					if(obj.scrollInterval) clearInterval(obj.scrollInterval);
					obj.animate = true;
					obj.dir = 'right';
					obj.slideRight();
				}
				return false;
			});
		}
	}
	// reveal frame
	this.frame.animate({
		opacity: 1
	}, 1500);
};
// Create interval
dScroll.prototype.createInterval =  function() {
	var obj = this;
	this.scrollInterval = setInterval(function() {
		obj.animate = true;
		obj.slideRight();
	}, this.intervalSpeed);
};
// moves the elements on the page in preparation for the slide
dScroll.prototype.shiftElementsLeft = function(shiftNumber) {
	if(this.slideInitFunc) this.slideInitFunc();
	this.container.left = this.container.left - shiftNumber * this.totalItemWidth;
	this.container.css('left', this.container.left + 'px');
	for(i=shiftNumber; i>0; i--) {
		$(this.slideItems[this.slideItems.length - 1]).insertBefore(this.slideItems[0]);
		this.slideItems = $(this.containerId + ' ' + this.itemClass);
	}

};
dScroll.prototype.shiftElementsRight = function(shiftNumber) {
	this.container.left = this.container.left + shiftNumber * this.totalItemWidth;
	this.container.css('left', this.container.left + 'px');
	for(i=shiftNumber; i>0; i--) {
		$(this.slideItems[0]).insertAfter(this.slideItems[this.slideItems.length - 1]);
		this.slideItems = $(this.containerId + ' ' + this.itemClass);
	}
	if(this.slideEndFunc) this.slideEndFunc();
	if(this.pageDots) this.resetSlide();	
	this.animate = false;
};
// slide elements left
dScroll.prototype.slideLeft = function() {
	var obj = this;
	this.container.left = this.container.left + this.totalSlide;
	$(this.slideItems).removeClass('active-slide');
	$(this.slideItems[obj.currSlide-1]).addClass('active-slide');
	this.container.animate({
		left: this.container.left
	}, this.speed, function() {if(obj.pageDots) { obj.resetSlide(); } if(obj.slideEndFunc) { obj.slideEndFunc(); } obj.animate = false;});
};
// slide elements right
dScroll.prototype.slideRight = function() {
	var obj = this;
	$(this.slideItems).removeClass('active-slide');
	$(this.slideItems[obj.currSlide]).addClass('active-slide');
	if(this.slideInitFunc) this.slideInitFunc();
	this.container.left = this.container.left - this.totalSlide;
	this.container.animate({
		left: this.container.left
	}, this.speed, function() {obj.shiftElementsRight(obj.currSlide);});
};
// create new page element for page dots
dScroll.prototype.makePageDots = function() {
	var last = '',
	i;
	this.frame.prepend('<div class="page-dots"></div>');
	this.dotContainer = this.frame.find('.page-dots');
	for(i=1; i<(this.slideItems.length/this.slideNumber)+1; i++) {
		if(i == this.slideItems.length/this.slideNumber) last = ' slide-dot-last';
		this.dotContainer.append('<a href="#" class="slide-dot slide-dot-'+i+last+'" rel="'+i+'">0'+i+'</a>');
	}
	this.dotLinks = this.dotContainer.find('.slide-dot');
	$(this.dotLinks[0]).addClass('active');
	this.curr = 1;
	// define css
	this.dotLinks.css('float', 'left');
	var dotContainer_css = {
		'position': 'absolute',
		'z-index': 50
	};
	this.dotContainer.css(dotContainer_css);
	this.addDotClick();
};
// add dot click event
dScroll.prototype.addDotClick = function() {
	var obj = this,
	skip;
	for(i=0; i<this.dotLinks.length; i++) {
		$(this.dotLinks[i]).click(function() {
		if(obj.scrollInterval) clearInterval(obj.scrollInterval);
			obj.curr = obj.dotContainer.find('.active').attr('rel')*1;
			skip = this.rel*1;
			if(!obj.animate && skip != obj.curr) {
				if(skip > obj.curr) {
					if(skip - obj.curr <= obj.slideItems.length - skip + obj.curr) {
						obj.dir = 'right';
						obj.currSlide = skip-obj.curr;
					} else {
						obj.dir = 'left';
						obj.currSlide = obj.slideItems.length - skip + obj.curr;
					}
				} else {
					if(obj.curr - skip < (obj.slideItems.length - obj.curr) + skip) {
						obj.dir = 'left';
						obj.currSlide = obj.curr - skip;
					} else {
						obj.dir = 'right';
						obj.currSlide = (obj.slideItems.length - obj.curr) + skip
					}
				}
				obj.totalSlide = Math.abs(obj.currSlide)*obj.totalItemWidth;
				if(obj.dir == 'right') {
					obj.animate = true;
					obj.slideRight();
				} else {
					obj.animate = true;
					obj.shiftElementsLeft(obj.currSlide);
					obj.slideLeft();
				}
			}
			return false;
		});
	}
};
// change page dot
dScroll.prototype.changePageDot = function() {
	if(this.dir == 'right') {
		this.curr = this.curr + this.currSlide;
	} else {
		this.curr = this.curr - this.currSlide;
	}
	if(this.curr > this.slideItems.length) {
		this.curr = this.curr%this.slideItems.length;
	} else if(this.curr <= 0) {
		this.curr = this.slideItems.length + this.curr;
	}
	this.dotContainer.find('.active').removeClass('active');
	$(this.dotLinks[this.curr - 1]).addClass('active');
};
// reset slide number
dScroll.prototype.resetSlide = function() {
	if(this.pageDots) this.changePageDot();
	this.totalSlide = this.slideNumber * this.totalItemWidth;
	this.currSlide = this.slideNumber;
	//this.currSpeed = (this.currSlide == 1) ? 1 : 1/this.currSlide;
};
