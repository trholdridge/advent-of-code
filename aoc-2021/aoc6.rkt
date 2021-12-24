;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname aoc6) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/batch-io)
(require 2htdp/image)
(require 2htdp/universe)
(require racket/string)
(require racket/base)

(define (sim lon)
  (big-bang lon
    [to-draw drawing]
    [on-tick inc 0.01 80]))

(define (drawing lon)
  (overlay (text (number->string (length lon)) 24 "black")
           (empty-scene 300 200)))

; new list of lanternfish
(define (inc lon)
  (cond
    [(empty? lon) '()]
    [(cons? lon) (if (>= (sub1 (first lon)) 0)
                     (cons (sub1 (first lon))
                           (inc (rest lon)))
                     (cons 8
                           (cons 6
                                 (inc (rest lon)))))]))

; -------------------

(define TOTAL-DAYS 256)
(define FISH-TABLE (make-vector (* 9 (+ TOTAL-DAYS 1)) #f))

(define (fish-table-calc lof)
  (foldr (λ (f so-far) (+ so-far (num-fish-from f TOTAL-DAYS)))
         0 lof))

(define (num-fish-from f days)
  (local [(define LOOKUP (vector-ref FISH-TABLE (+ f (* 9 days))))]
    (cond
      [(number? LOOKUP) LOOKUP]
      [(<= days f) 1]
      [else (vector-set! FISH-TABLE
                         (+ f (* 9 days))
                         ; fish spawned by next child
                         (+ (num-fish-from 8 (- days (+ 1 f)))
                            ; fish spawned by this fish excluding ^
                            (num-fish-from 6 (- days (+ 1 f)))))
            (vector-ref FISH-TABLE (+ f (* 9 days 1)))])))

; -------------------

(define RAW-INPUT (read-1strings "input6.txt"))
(define INPUT-AAA (map string->number RAW-INPUT))

(define (process l)
  (cond
    [(empty? l) '()]
    [(cons? l) (if (boolean? (first l))
                   (process (rest l))
                   (cons (first l)
                         (process (rest l))))]))

(define INPUT (process INPUT-AAA))
