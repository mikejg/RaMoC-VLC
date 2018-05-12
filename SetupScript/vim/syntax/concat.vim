
" Concat pattern language

if exists("b:current_syntax")
  finish
endif

syn sync linebreaks=1

syn case ignore

syn match   item                  /^:[^ ]*/
syn match   comment               /^##.*/


syn region nativerule start=/with {/ end=/^--/

syn match   from                  /\(^:[^ ]*\)\@<=.*\(=>\)\@=/
syn match   from                  /\(^:[^ ]*\)\@<=.*\(==>\)\@=/

syn match   to                    /\(=>\)\@<=.*/
syn match   to                    /\(=>\)\@<=.*\(with.*\)\@=/

syn match   arrow                 /==>/
syn match   arrow                 /=>/

"TODO pimp color

hi from           term=bold cterm=bold ctermfg=White gui=bold guifg=White
"hi to             term=bold cterm=bold ctermfg=Brown gui=bold guifg=Brown
hi arrow          term=bold cterm=bold ctermfg=Red gui=bold guifg=Red

hi item           term=bold cterm=bold ctermfg=Green gui=bold guifg=Green
hi to             term=bold cterm=bold ctermfg=Yellow gui=bold guifg=Yellow
hi comment        term=bold cterm=bold ctermfg=Magenta  gui=bold guifg=Magenta

hi nativerule     term=bold cterm=bold ctermfg=Blue gui=bold guifg=Blue

let b:current_syntax = "concat"

