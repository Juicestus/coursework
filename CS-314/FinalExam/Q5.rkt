#lang racket


(define (reverse ls)
  (cond
    [(null? ls) '()]
    [else (append (reverse (cdr ls)) (list (car ls)))]
  )
)

(print (reverse '(1 2 3 4)))
(newline)

