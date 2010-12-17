function [X,Y,S,F] = sally_struct2mat(fvec)
% Converts a Matlab structure generated by Sally to individual 
% matrices and cell arrays.
%
% Input:
%  fvec   - Structure generated by Sally
% 
% Output:
%  X      - Data matrix (dim x num)
%  Y      - Label vector (1 x num)
%  S      - Cell array of sources (1 x num)
%  F      - Cell array of features (non-zero dimensions)
% 

X = [fvec.data];
Y = [fvec.label];
S = {fvec.src};
F = {fvec.feat};