#ifndef SPLITER_H
#define SPLITER_H

/**
 * [spliter description]
 * @param tq   [description]
 * @param task [description]
 */
void spliter(task_queue_t *tq, task_t *task);

/**
 * cree une tache contenant les infos pour split un fichier
 * en plusieurs fichiers et qui lance une autre tache sur
 * chacune de ces parties (avec le nom du fichier, l'offset de
 * debut et le nombre de char/wchar a traiter)
 *
 * @param  fp         le chemin vers le fichier a traiter
 * @param  n          le nombre de decoupes
 * @param  d          the delimiter (wchar_t*)
 * @param  createTask pointeur sur fonction qui cree une tache
 * @return            une tache
 */
task_t *createSplitTask(const char *fp, int n, wchar_t *d, void *createTask);

// Note : if setlocale(LC_ALL, "fr_FR.utf8"); doesn't worker
// you have to user locale-gen fr_FR.utf8 to add it to your system


#endif
