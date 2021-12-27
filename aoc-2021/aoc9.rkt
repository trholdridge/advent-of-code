#lang racket

(require 2htdp/batch-io)
(require racket/string)

(define INPUT (read-lines "input9.txt"))
(define ROWS (length INPUT))
(define COLS (string-length (first INPUT)))


(define (index->row n)
  (truncate (/ n COLS)))

(define (index->col n)
  (modulo n COLS))

(define GRID
  (build-vector (* ROWS COLS)
                (λ (n) (string->number (substring (list-ref INPUT
                                                            (index->row n))
                                                  (index->col n)
                                                  (+ 1 (index->col n)))))))
; --------------------

; solve
(define (solve _)
  (foldr (λ (index so-far) (+ so-far 1 (vector-ref GRID index)))
         (local-lows GRID)))

; local-lows : _ -> [List-of Nat]
; gets all the indices of local minimums
(define (local-lows _)
  (filter (λ (n) (is-local-low? n))
          (build-list (* ROWS COLS) values)))

; is-local-low? : Nat -> Boolean
; is the number at the given index a local horizontal min?
(define (is-local-low? index)
  (local [(define ROW (index->row index))
          (define COL (index->col index))
          (define VAL (vector-ref GRID index))
          (define F-ROW (<= ROW 0))
          (define L-ROW (>= ROW (- ROWS 1)))
          (define F-COL (<= COL 0))
          (define L-COL (>= COL (- COLS 1)))]))