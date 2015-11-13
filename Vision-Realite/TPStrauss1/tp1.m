NomGenerique = 'Turtle' ;
Suffixe = '.tif' ;
Nom = sprintf('%sG%s',NomGenerique,Suffixe) ;
ImageGauche = double(imread(Nom)) ;
figure(1) ; hold off ; image(uint8(ImageGauche)) ;  hold on ; axis image ;  
title('Image gauche') ; colormap(gray(256)) ; drawnow ;
Nom = sprintf('%sD%s',NomGenerique,Suffixe) ;
ImageDroite = double(imread(Nom)) ;
figure(2) ;  hold off ; image(uint8(ImageDroite)) ;  hold on ; axis image ; 
title('Image droite') ; colormap(gray(256)) ; drawnow ;
[Nlin, Ncol, Nplan] = size(ImageGauche) ;  
% Nombre de points que l’on va sélectionner sur les images
NombreDePoints = 16 ;
PointDroite = ones(NombreDePoints,3) ;
PointGauche = ones(NombreDePoints,3) ;

theta = 1;
LD = [-16,12,89];
y_min = 0;
y_max = 461;
x_min = 0;
x_max = 267;

if ( ( theta <= pi/2 ) && ( theta >= -pi/2 ) ) || ( ( theta >= 3*pi/2 ) && (theta <= -3*pi/2 ) )
  y_min = ( -LD(3) - ( LD(1) * x_min ) ) / LD(2) ;
  y_max = ( -LD(3) - ( LD(1) * x_max ) ) / LD(2) ;
else    
  x_min = ( -LD(3) - ( LD(2) * y_min ) ) / LD(1) ;
  x_max = ( -LD(3) - ( LD(2) * y_max ) ) / LD(1) ;
end
figure(2) ; 
line( [x_min,x_max] , [y_min,y_max] , 'color', 'r' ) ; 
drawnow ;

for n=1:NombreDePoints
    figure(1) ; drawnow ;
    [x,y] = ginput(1) ;
    plot(x,y,'bo') ;
    PointGauche(n,1:2) = [x,y] ;
    figure(2) ; drawnow ;
    [x,y] = ginput(1) ;
    plot(x,y,'ro') ;
    PointDroite(n,1:2) = [x,y] ;
end
