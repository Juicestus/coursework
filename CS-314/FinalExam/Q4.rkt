#lang racket

(define (positivityTest ls)
  (cond
    [(null? ls) '()]
    [else (cons (> (car ls) 0)  (positivityTest (cdr ls)))]
  )
)

; testing:

(print (positivityTest '(1 2 -3 4)))
(newline)