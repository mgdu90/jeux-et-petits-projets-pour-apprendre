let carte_a =
"
╔════════╗
║    A   ║
╠════════╣
║        ║
║ /\\_/\\  ║
║( o o ) ║
║ > ^ <  ║
║        ║
╚════════╝
"

let carte_b = 
"
╔════════╗
║    B   ║
╠════════╣
║        ║
║  O O   ║
║  =^=   ║
║        ║
║        ║
╚════════╝
"

let carte_c = 
"
╔════════╗
║    C   ║
╠════════╣
║        ║
║  \\_/   ║
║  =( )= ║
║  ( )   ║
║        ║
╚════════╝
"

let carte_d = 
"
╔════════╗
║    D   ║
╠════════╣
║        ║
║  @ @   ║
║   ~    ║
║  \\_/_  ║
║        ║
╚════════╝
"

let carte_e = 
"
╔════════╗
║    E   ║
╠════════╣
║        ║
║  /|\\   ║
║ / | \\  ║
║/_ | _\\ ║
║        ║
╚════════╝
"

let carte_f = 
"
╔════════╗
║    F   ║
╠════════╣
║        ║
║  /'\\   ║
║ ( o )  ║
║  `'`   ║
║        ║
╚════════╝
"

let carte_g = 
"
╔════════╗
║    G   ║
╠════════╣
║        ║
║  / \\   ║
║ (   )  ║
║  `-'   ║
║        ║
╚════════╝
"

let carte_h = 
"
╔════════╗
║    H   ║
╠════════╣
║        ║
║ /_|\\   ║
║ \\|_/_  ║
║        ║
║        ║
╚════════╝
"

let carte_a2 =
"
╔════════╗
║    A   ║
╠════════╣
║        ║
║ /\\_/\\  ║
║( o o ) ║
║ > ^ <  ║
║        ║
╚════════╝
"

let carte_b2 = 
"
╔════════╗
║    B   ║
╠════════╣
║        ║
║  O O   ║
║  =^=   ║
║        ║
║        ║
╚════════╝
"

let carte_c2 = 
"
╔════════╗
║    C   ║
╠════════╣
║        ║
║  \\_/   ║
║  =( )= ║
║  ( )   ║
║        ║
╚════════╝
"

let carte_d2 = 
"
╔════════╗
║    D   ║
╠════════╣
║        ║
║  @ @   ║
║   ~    ║
║  \\_/_  ║
║        ║
╚════════╝
"

let carte_e2 = 
"
╔════════╗
║    E   ║
╠════════╣
║        ║
║  /|\\   ║
║ / | \\  ║
║/_ | _\\ ║
║        ║
╚════════╝
"

let carte_f2 = 
"
╔════════╗
║    F   ║
╠════════╣
║        ║
║  /'\\   ║
║ ( o )  ║
║  `'`   ║
║        ║
╚════════╝
"

let carte_g2 = 
"
╔════════╗
║    G   ║
╠════════╣
║        ║
║  / \\   ║
║ (   )  ║
║  `-'   ║
║        ║
╚════════╝
"

let carte_h2 = 
"
╔════════╗
║    H   ║
╠════════╣
║        ║
║ /_|\\   ║
║ \\|_/_  ║
║        ║
║        ║
╚════════╝
"

let dos = 
"
╔════════╗
║ MEMORY ║
╠════════╣
║-D------║
║--------║
║---O----║
║--------║
║-----S--║
╚════════╝
"

(* fonction qui affiche 8 cartes cote a cote dans le terminal *)
let cote_a_cote carte_1 carte_2 carte_3 carte_4 carte_5 carte_6 carte_7 carte_8 =
  let lines_1 = Array.of_list (String.split_on_char '\n' carte_1) in
  let lines_2 = Array.of_list (String.split_on_char '\n' carte_2) in
  let lines_3 = Array.of_list (String.split_on_char '\n' carte_3) in
  let lines_4 = Array.of_list (String.split_on_char '\n' carte_4) in
  let lines_5 = Array.of_list (String.split_on_char '\n' carte_5) in
  let lines_6 = Array.of_list (String.split_on_char '\n' carte_6) in
  let lines_7 = Array.of_list (String.split_on_char '\n' carte_7) in
  let lines_8 = Array.of_list (String.split_on_char '\n' carte_8) in
  for i = 0 to (Array.length lines_1 - 1) do
    print_endline (lines_1.(i) ^ "  " ^ lines_2.(i) ^ "  " ^ lines_3.(i) ^ "  " ^ lines_4.(i) ^ "  " ^ lines_5.(i) ^ "  " ^ lines_6.(i) ^ "  " ^ lines_7.(i) ^ "  " ^ lines_8.(i))
  done

(* declaration du jeu qui sera derriere les cartes ainsi que du jeu qui sera affiche *)
let jeu = [|carte_a; carte_b; carte_c; carte_d; carte_e; carte_f; carte_g; carte_h; carte_a2; carte_b2; carte_c2; carte_d2; carte_e2; carte_f2; carte_g2; carte_h2|]
let jeu_affichable = [|dos; dos; dos; dos; dos; dos; dos; dos; dos; dos; dos; dos; dos; dos; dos; dos|]

(* fonction qui servira pour melanger le jeu de cartes *)
let swap a i j =
  let t = a.(i) in a.(i) <- a.(j); a.(j) <- t

(* fonction qui melange un tableau *)
let melange a =
  for i = 1 to Array.length a - 1 do
    let j = Random.int (i + 1) in (* entre 0 et i inclus *)
    swap a i j
  done

(* fonction qui convertit les coordonnees dans une matrice 2 * 8 en coordonees dans un tableau qui represente la matrice *)
let coordonnees_matriciels_en_lineaire var =
  let acc = ref 0 in
    if var.[2] = '2' then acc := !acc + 8 
    else acc := !acc + 0;
    if var.[0] = 'b' then acc := !acc + 1 
    else if var.[0] = 'c' then acc := !acc + 2
    else if var.[0] = 'd' then acc := !acc + 3
    else if var.[0] = 'e' then acc := !acc + 4
    else if var.[0] = 'f' then acc := !acc + 5
    else if var.[0] = 'g' then acc := !acc + 6
    else if var.[0] = 'h' then acc := !acc + 7;
    !acc;;

(* melange de la liste des cartes *)
Random.self_init ();
melange jeu

(* fonction qui affiche le jeu *)
let afficher_jeu tab =
  cote_a_cote tab.(0) tab.(1) tab.(2) tab.(3) tab.(4) tab.(5) tab.(6) tab.(7);
  cote_a_cote tab.(8) tab.(9) tab.(10) tab.(11) tab.(12) tab.(13) tab.(14) tab.(15)

(* declaration du compteur de tours *)
let compteur = ref 0

(* programme principale qui se charge de l affichage *)
let () = 
  while jeu_affichable <> jeu do
    afficher_jeu jeu_affichable;

    (* explication des consignes *)
    print_endline "les colonnes sont indexees par les lettres de \"a\" a \"h\" et les lignes par les numeros \"1\" et \"2\"";
    print_endline "les commandes que vous rentrerez auront la forme suivante <colonne> <ligne>";
    print_endline "sans espace avant ou apres et avec un espace entre les deux caracteres de votre commande";

    (* jeu *)
    print_string "entrez votre commande ici -> ";
    let commande = read_line () in
    let indice = coordonnees_matriciels_en_lineaire commande in
    assert (jeu_affichable.(indice) == dos);
    jeu_affichable.(indice) <- jeu.(indice);
    afficher_jeu jeu_affichable;

    (* jeu *)
    print_string "entrez votre autre commande ici -> ";
    let commande2 = read_line () in
    let indice2 = coordonnees_matriciels_en_lineaire commande2 in
    assert (jeu_affichable.(indice2) == dos);
    jeu_affichable.(indice2) <- jeu.(indice2);
    afficher_jeu jeu_affichable;
    compteur := !compteur + 1;

    (* gestion de la partie selon la commande de l utilisateur si les deux cartes sont identiques elles restent retournees et sinon elles sont cachees *)
    (* du temps est laisse au joueur pour memoriser les cartes *)
    if jeu_affichable.(indice2) = jeu_affichable.(indice) then 
      begin
        print_endline "gg";
        print_endline "appuyez sur entree quand c est bon";
        let var2 = read_line () in print_endline var2
      end
    else
      begin
        print_endline "dommage";
        jeu_affichable.(indice) <- dos;
        jeu_affichable.(indice2) <- dos;
        print_endline "appuyez sur entree quand c est bon";
        let var2 = read_line () in print_endline var2
      end
  done

(* affichage de la fin de partie et petit message d au revoir *)
let () = 
Printf.printf "bien joue vous avez reussi en %d coups \n" !compteur
