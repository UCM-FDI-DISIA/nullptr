// Rotacion de los engranajes con el scroll lateral derecho
document.addEventListener('scroll', function() {
  var rotation = this.documentElement.scrollTop * 0.25;
  engranajeIzq.style.transform = 'rotate(' + rotation + 'deg)';
  engranajeDer.style.transform = 'rotate(' + -rotation + 'deg)';
  engranaje1.style.transform = 'rotate(' + rotation + 'deg)';
  engranaje2.style.transform = 'rotate(' + -rotation + 'deg)';
  engranaje3.style.transform = 'rotate(' + rotation + 'deg)';
  engranaje4.style.transform = 'rotate(' + -rotation + 'deg)';
  engranaje5.style.transform = 'rotate(' + rotation + 'deg)';
  engranaje6.style.transform = 'rotate(' + -rotation + 'deg)';
  engranaje7.style.transform = 'rotate(' + rotation + 'deg)';
  engranaje8.style.transform = 'rotate(' + -rotation + 'deg)';
  engranaje9.style.transform = 'rotate(' + rotation + 'deg)';
  engranaje10.style.transform = 'rotate(' + -rotation + 'deg)';
});

let slideIndex = 1;

document.addEventListener('DOMContentLoaded', function() {
  showSlides(slideIndex);
});

// Next/previous controls
function plusSlides(n) {
  showSlides(slideIndex += n);
}

// Thumbnail image controls
function currentSlide(n) {
  showSlides(slideIndex = n);
}

function showSlides(n) {
  let i;
  let slides = document.getElementsByClassName("mySlides");
  let dots = document.getElementsByClassName("dot");
  if (n > slides.length) {slideIndex = 1}
  if (n < 1) {slideIndex = slides.length}
  for (i = 0; i < slides.length; i++) {
    slides[i].style.display = "none";
  }
  for (i = 0; i < dots.length; i++) {
    dots[i].className = dots[i].className.replace(" active", "");
  }
  slides[slideIndex-1].style.display = "block";
  dots[slideIndex-1].className += " active";
}