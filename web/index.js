// Rotacion de los engranajes con el scroll lateral derecho
document.addEventListener('scroll', function() {
  var rotation = this.documentElement.scrollTop * 0.25;
  engranaje1.style.transform = 'rotate(' + rotation + 'deg)';
  engranaje2.style.transform = 'rotate(' + -rotation + 'deg)';
});