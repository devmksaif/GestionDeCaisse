#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


//Macros
#define MAX_LINE_LENGTH 256



//Structures des donnés


typedef struct ReceiptNode * ReceiptNodes;
typedef struct ReceiptNode {
    char *receipt;
    ReceiptNodes next;
} ReceiptNode;


typedef struct
{
    GtkBuilder *builder;

} CallbackData;




typedef struct
{
    gint quantityDataInt;
} quantityData;




typedef struct
{
    char productName[50];
    char productDescription[500];
    char  productQuantity[700];
    char productPrice[700];
    char productRef[100];

} Product;

typedef struct {
    char UserName[70];
    char Password[70];
    char Role[70];

} User;

typedef struct mainNode *productNode;
typedef struct mainNode
{
    Product product;
    productNode next;
} mainNode;

typedef struct userNode *usersNode;
typedef struct userNode
{
    User user;
    usersNode next;
} userNode;

typedef struct
{
    productNode mainNode;
    ReceiptNodes receiptNode;
    GtkListStore * newListStore;
    GtkTreeView *treeview;
    usersNode users;
} rechercheData;

typedef struct {
    rechercheData * rech1;
    rechercheData * rech2;

} rechDataTab;



typedef struct
{
    GtkEntry * nom;
    GtkEntry * desc;
    GtkEntry * prix;
    GtkEntry * quant;
    GtkEntry * ref;
    rechDataTab* recherchedata;
    GtkWindow * prodAddWindow;



}       fieldsData;

typedef struct getData
{
    gchar * n;
    gchar * d;
    gchar * p;
    gchar * q;
    gchar * r;
    GtkEntry * text;
    GtkTreeModel * model;
    GtkTreeIter iter;
    GtkTreeSelection * selection;
    productNode Node;
    GtkButton * getProcCaisse;
    GtkLabel * label;
    GtkBuilder * builder;

} getData;

typedef struct
{
    GtkWidget * getButton;
    GtkWidget * getButton2;
    GtkBuilder *builder;
    productNode Node;
    GtkLabel * label;
} getWidget;

typedef struct getElementsUser {

    gchar *UserName;
    gchar *Password;
    gchar *Role;
    usersNode nodeUsers;

} getElementsUser;


typedef struct getElementsNew {
    GtkBuilder * builder;
    GtkBuilder * builder2;
    usersNode nodeUsers;
    GtkTreeView * tree;
    GtkListStore * store;
}getElementsNew;

guint timer_id = 0;
getElementsNew * globElem;

//Var globales
gchar * userG;
gchar * passG;


//Les fonctions declarés

char ** splitText(char  *  text, char sep);
int length(char * text);
int wordCount(char * text, char sep);
char* sanitize_string(char * string, char sep);
void removeFirstChar(char *str);
void check_login(GtkWidget * widget,  gpointer data);
void addProducts(GtkTreeView *treeProds, GtkListStore *listStore, gchar *productName, gchar *productDescription, gchar *productPrice, gchar *productQuantity, gchar *productRef);
void Dashboard(GtkBuilder * mainDashBoard, usersNode  Users);
productNode createProduct(Product product);
void addColumns(gchar * title, GtkTreeView * treeView, gint index);
void readFromFile(const char * filename, productNode main_node);
int readFromFileUsers(const char * filename, const char * username , const char *password,  usersNode * Users);
void  listProduitsGetSelected(GtkTreeView *listProd, getWidget *Widget);
void addColumns(gchar *title, GtkTreeView *treeView, gint index);
void ajoutDansLaCaisse(GtkWidget *widget, gpointer data);
gboolean remove_selections(GtkWidget *widget, GdkEvent *event, gpointer user_data);
void recherche_produits(GtkEditable * widget, gpointer data);
void populateTableAgain(productNode mainNode, rechercheData * recherchedata);
void load_css(GtkWidget *widget, const gchar *filename, const gchar *className);
void addProduitNouveau(GtkWidget * widget,  gpointer data);
void handleAddProduct(GtkWidget * widget, gpointer data);
void handleSelectedProdSuppr(GtkTreeSelection * selected_prod, gpointer data);
void listProduitsGetSelectedStock(GtkTreeView * listProd, getWidget *Widget);
void handleMontant(GtkEditable * entryMontant , gpointer data);
void addProdCaisse(GtkTreeView *treeProds, GtkListStore *listStore, gchar *productName, gchar *productDescription, gchar *productPrice, gchar *productQuantity);
void iterate_columns_data(GtkTreeView *treeview, GtkBuilder * builder,getData * data);
void handleMontant(GtkEditable * entryMontant , gpointer data);
void disable_notebook_tab(GtkNotebook *notebook, gint page_num);
void enable_notebook_tab(GtkNotebook *notebook, gint page_num);
int getItemsCount(GtkTreeView *treeView);
void handleCaissePress(GtkWidget * widget , gpointer data);
void addProductsRec(GtkTreeView *treeProds, GtkListStore *listStore, gchar *Recette, gchar * Id);
ReceiptNodes createReceiptNode(const char *receiptContent);
void readFromFileReceipt(const char *filename, ReceiptNodes *main_node);
void recherche_vendeur(GtkEditable *widget, gpointer data);
void populateTableAgainRec(ReceiptNodes mainNode, rechercheData * recherchedata);
void disable_visible_notebook_tab(GtkWidget *notebook, int page_num);
char *trim(char *str);
void recherche_utd(GtkEditable *widget, gpointer data);
void populateTableAgainUser(usersNode mainNode, rechercheData * recherchedata);
void on_window_destroy(GtkWidget *widget, gpointer data);
gboolean update_label(gpointer user_data);
void start_timer(getElementsNew *elem);
void stop_timer();
void remove_selected_rows(GtkButton *button, gpointer data);
void on_selected_caisse_item(GtkTreeView *treeview, gpointer data);
void increment_to_montant1(GtkButton *widget, gpointer data);
void increment_to_montant2(GtkButton *widget, gpointer data);
void increment_to_montant3(GtkButton *widget, gpointer data);
void increment_to_montant4(GtkButton *widget, gpointer data);
void increment_to_montant5(GtkButton *widget, gpointer data);
void increment_to_montant6(GtkButton *widget, gpointer data);
void increment_to_montant7(GtkButton *widget, gpointer data);
void increment_to_montant8(GtkButton *widget, gpointer data);
void increment_to_montant9(GtkButton *widget, gpointer data);
void increment_to_montant10(GtkButton *widget, gpointer data);
void navToCaisse(GtkWidget *widget, gpointer data);
void supprtouscaisseFunc(GtkWidget *widget, gpointer data);
void show_error_dialog(GtkWindow *parent, const gchar *message);
void on_add_user_submit(GtkButton *button, gpointer user_data);
void ajouter_nouveau_ut(GtkWidget *widget, gpointer data);
// Variables Global
GtkListStore * CAISSE_LISTSTORE;
GtkWidget *quantity_dialog = NULL;

ReceiptNodes headG = NULL;




gboolean update_label(gpointer user_data) {
    getElementsNew * elem = (getElementsNew * ) user_data;
    usersNode CurrentUsers = elem->nodeUsers;
    GtkListStore * users_store = GTK_LIST_STORE(gtk_tree_view_get_model(elem->tree));
    gtk_list_store_clear(users_store);
  while (CurrentUsers != NULL) {

        addUsers(elem->tree,users_store,CurrentUsers->user.UserName,"########",CurrentUsers->user.Role);
        CurrentUsers = CurrentUsers->next;

    }

    return G_SOURCE_CONTINUE;
}



void start_timer(getElementsNew * elem) {
    if (timer_id == 0) {

        timer_id = g_timeout_add(1000, update_label, elem);
        globElem = elem;
    }
}

void stop_timer() {
    if (timer_id != 0) {

        g_source_remove(timer_id);
        timer_id = 0;
    }
}


void remove_selected_rows(GtkButton * button, gpointer data) {
    GtkBuilder *builder = (GtkBuilder * ) data;
    GtkTreeView *  treeview;
    treeview = GTK_TREE_VIEW(gtk_builder_get_object(builder,"les_items_caisse"));
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    GtkListStore *list_store = GTK_LIST_STORE(model);
    GtkTreeIter iter;
    GList *list = gtk_tree_selection_get_selected_rows(selection, &model);
    GList *node = list;
    GtkWidget * notebook;
    GtkLabel * total_sum;
    GtkLabel * rendu;
    GtkEntry * mont;
    notebook = GTK_NOTEBOOK(gtk_builder_get_object(builder,"noteMain"));
    total_sum= GTK_LABEL(gtk_builder_get_object(builder,"total_sum"));
    rendu= GTK_LABEL(gtk_builder_get_object(builder,"rendu"));
    mont= GTK_ENTRY(gtk_builder_get_object(builder,"montant"));



    gchar *value;
    while (node != NULL) {
        GtkTreePath *path = (GtkTreePath *)node->data;
        if (gtk_tree_model_get_iter(model, &iter, path)) {
            if (gtk_tree_selection_get_selected(selection, &model, &iter)) {

        gtk_tree_model_get(model, &iter, 3, &value, -1);
        gfloat r = strtof(gtk_label_get_text(total_sum),NULL) - strtof(value,NULL);
             char buff[60];
        sprintf(buff,"%.2f",r);

        gtk_label_set_text(total_sum,buff);

            char buffSum[60];

                if (strtof(gtk_entry_get_text(mont), NULL) > 0) {
                    gfloat xd = strtof(gtk_entry_get_text(mont), NULL) - r ;  // Use the updated 'r' value
                    sprintf(buffSum, "%.2f", xd);
                    gtk_label_set_text(rendu, buffSum);
                }



        g_free(value);
    }
            gtk_list_store_remove(list_store, &iter);
                gtk_tree_selection_unselect_all(selection);

        }
        gtk_tree_path_free(path);
        node = node->next;
        break;
    }
    gtk_tree_view_set_model(treeview,model);


    int itemsCount = getItemsCount(treeview);
    if(itemsCount == 0)
    {
    disable_notebook_tab(GTK_NOTEBOOK(notebook),2);


    gtk_entry_set_text(mont,"");
    gtk_label_set_text(rendu,"0.0");
    gtk_label_set_text(total_sum,"0.0");
    }

    g_list_free(list);
}

void on_selected_caisse_item(GtkTreeView * treeview , gpointer data)
{
    GtkBuilder * builder = (GtkBuilder * ) data;
     GtkButton * suppr_element_caisse;
    suppr_element_caisse = GTK_BUTTON(gtk_builder_get_object(builder,"supprunelem"));
    gtk_widget_set_sensitive(suppr_element_caisse,TRUE);
    g_signal_connect(suppr_element_caisse, "clicked", G_CALLBACK(remove_selected_rows), builder);
}

void increment_to_montant1(GtkButton * widget,gpointer data)
{
    GtkBuilder * builder=  (GtkBuilder*) data;
    GtkEntry *mont = GTK_ENTRY(gtk_builder_get_object(builder,"montant"));
    gchar * text = gtk_button_get_label(widget);
    gchar * montText = gtk_entry_get_text(mont);
    gchar buffer[256];
    sprintf(buffer, "%s%s",montText,text);

    gtk_entry_set_text(mont,buffer);
}
void increment_to_montant2(GtkButton * widget,gpointer data)
{
    GtkBuilder * builder=  (GtkBuilder*) data;
    GtkEntry *mont = GTK_ENTRY(gtk_builder_get_object(builder,"montant"));
    gchar * text = gtk_button_get_label(widget);
    gchar * montText = gtk_entry_get_text(mont);
    gchar buffer[256];
    sprintf(buffer, "%s%s",montText,text);

    gtk_entry_set_text(mont,buffer);
}

void increment_to_montant3(GtkButton * widget,gpointer data)
{
    GtkBuilder * builder=  (GtkBuilder*) data;
    GtkEntry *mont = GTK_ENTRY(gtk_builder_get_object(builder,"montant"));
    gchar * text = gtk_button_get_label(widget);
    gchar * montText = gtk_entry_get_text(mont);
    gchar buffer[256];
    sprintf(buffer, "%s%s",montText,text);

    gtk_entry_set_text(mont,buffer);
}
void increment_to_montant4(GtkButton * widget,gpointer data)
{
    GtkBuilder * builder=  (GtkBuilder*) data;
    GtkEntry *mont = GTK_ENTRY(gtk_builder_get_object(builder,"montant"));
    gchar * text = gtk_button_get_label(widget);
    gchar * montText = gtk_entry_get_text(mont);
    gchar buffer[256];
    sprintf(buffer, "%s%s",montText,text);

    gtk_entry_set_text(mont,buffer);
}
void increment_to_montant5(GtkButton * widget,gpointer data)
{
    GtkBuilder * builder=  (GtkBuilder*) data;
    GtkEntry *mont = GTK_ENTRY(gtk_builder_get_object(builder,"montant"));
    gchar * text = gtk_button_get_label(widget);
    gchar * montText = gtk_entry_get_text(mont);
    gchar buffer[256];
    sprintf(buffer, "%s%s",montText,text);

    gtk_entry_set_text(mont,buffer);
}
void increment_to_montant6(GtkButton * widget,gpointer data)
{
    GtkBuilder * builder=  (GtkBuilder*) data;
    GtkEntry *mont = GTK_ENTRY(gtk_builder_get_object(builder,"montant"));
    gchar * text = gtk_button_get_label(widget);
    gchar * montText = gtk_entry_get_text(mont);
    gchar buffer[256];
    sprintf(buffer, "%s%s",montText,text);

    gtk_entry_set_text(mont,buffer);
}
void increment_to_montant7(GtkButton * widget,gpointer data)
{
    GtkBuilder * builder=  (GtkBuilder*) data;
    GtkEntry *mont = GTK_ENTRY(gtk_builder_get_object(builder,"montant"));
    gchar * text = gtk_button_get_label(widget);
    gchar * montText = gtk_entry_get_text(mont);
    gchar buffer[256];
    sprintf(buffer, "%s%s",montText,text);

    gtk_entry_set_text(mont,buffer);
}
void increment_to_montant8(GtkButton * widget,gpointer data)
{
    GtkBuilder * builder=  (GtkBuilder*) data;
    GtkEntry *mont = GTK_ENTRY(gtk_builder_get_object(builder,"montant"));
    gchar * text = gtk_button_get_label(widget);
    gchar * montText = gtk_entry_get_text(mont);
    gchar buffer[256];
    sprintf(buffer, "%s%s",montText,text);

    gtk_entry_set_text(mont,buffer);
}
void increment_to_montant9(GtkButton * widget,gpointer data)
{
    GtkBuilder * builder=  (GtkBuilder*) data;
    GtkEntry *mont = GTK_ENTRY(gtk_builder_get_object(builder,"montant"));
    gchar * text = gtk_button_get_label(widget);
    gchar * montText = gtk_entry_get_text(mont);
    gchar buffer[256];
    sprintf(buffer, "%s%s",montText,text);

    gtk_entry_set_text(mont,buffer);
}

void increment_to_montant10(GtkButton * widget,gpointer data)
{
    GtkBuilder * builder=  (GtkBuilder*) data;
    GtkEntry *mont = GTK_ENTRY(gtk_builder_get_object(builder,"montant"));
    gchar * text = gtk_button_get_label(widget);
    gchar * montText = gtk_entry_get_text(mont);
    gchar buffer[256];
    sprintf(buffer, "%s%s",montText,text);

    gtk_entry_set_text(mont,buffer);
}

void navToCaisse(GtkWidget * widget, gpointer data)
{
        gtk_notebook_set_current_page(GTK_NOTEBOOK(data), 2);

}

void supprtouscaisseFunc(GtkWidget * widget , gpointer data)
{
    GtkBuilder * builder = (GtkBuilder*)data;
    GtkTreeView *treeCaisse;
    GtkWidget * notebook;
    GtkLabel * total_sum;
    GtkLabel * rendu;
    GtkEntry * mont;
    treeCaisse = GTK_TREE_VIEW(gtk_builder_get_object(builder,"les_items_caisse"));
    notebook = GTK_NOTEBOOK(gtk_builder_get_object(builder,"noteMain"));
    total_sum= GTK_LABEL(gtk_builder_get_object(builder,"total_sum"));
    rendu= GTK_LABEL(gtk_builder_get_object(builder,"rendu"));
    mont= GTK_ENTRY(gtk_builder_get_object(builder,"montant"));
    GtkTreeModel *model = gtk_tree_view_get_model(treeCaisse);

    GtkListStore *list_store = GTK_LIST_STORE(model);
    gtk_list_store_clear(list_store);
    gtk_tree_view_set_model(treeCaisse,GTK_TREE_MODEL(list_store));
    int  itemsCount = getItemsCount(treeCaisse);
    if (itemsCount == 0) {
        disable_notebook_tab(GTK_NOTEBOOK(notebook),2);
    }

    gtk_entry_set_text(mont,"");
    gtk_label_set_text(rendu,"0.0");
    gtk_label_set_text(total_sum,"0.0");
}
void show_error_dialog(GtkWindow *parent, const gchar *message) {
    GtkWidget *dialog = gtk_message_dialog_new(
        parent,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_ERROR,
        GTK_BUTTONS_OK,
        "%s",
        message
    );
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void on_add_user_submit(GtkButton *button, gpointer user_data) {
    getElementsNew *elem = (getElementsNew*) user_data;
    GtkTreeView *tree;

    tree = GTK_TREE_VIEW(gtk_builder_get_object(elem->builder2, "users_tree"));

    GtkListStore *users_store = GTK_LIST_STORE(gtk_tree_view_get_model(tree));


    GtkWindow *parent_window = GTK_WINDOW(gtk_builder_get_object(elem->builder, "add_ut"));
    GtkEntry *user = GTK_ENTRY(gtk_builder_get_object(elem->builder, "user"));
    GtkEntry *password = GTK_ENTRY(gtk_builder_get_object(elem->builder, "pass"));
    GtkEntry *role_c = GTK_ENTRY(gtk_builder_get_object(elem->builder, "role_entry"));

    const gchar *username = gtk_entry_get_text(user);
    const gchar *password_text = gtk_entry_get_text(password);
    const gchar *role = gtk_entry_get_text(role_c);

    if (g_strcmp0(username, "") == 0 || g_strcmp0(password_text, "") == 0) {
        show_error_dialog(parent_window, "Username or password cannot be empty.");
        return;
    }

    if (strcmp(role, "emp") != 0 && strcmp(role, "admin") != 0) {
        show_error_dialog(NULL, "Role must be either 'emp' or 'admin'.");
        return;
    }

    getElementsUser *new_element = g_new(getElementsUser, 5);  // Fixed size argument to 1
    new_element->UserName = g_strdup(username);
    new_element->Password = g_strdup(password_text);
    new_element->Role = g_strdup(role);

        usersNode CurrentUsers = elem->nodeUsers;
    while(CurrentUsers->next != NULL)
    {
        CurrentUsers = CurrentUsers->next;
    }







    FILE *users = fopen("users.txt", "a+");
    fprintf(users, "%s,%s,%s,\n", username, password_text, role);
    fclose(users);

    User tmp;
    usersNode tmpd = (usersNode)malloc(sizeof(userNode));
    strcpy(tmp.UserName,username);
    strcpy(tmp.Password,password_text);
    strcpy(tmp.Role,role);


    tmpd->user = tmp;
    tmpd->next = NULL;
     CurrentUsers->next = tmpd;







    gtk_widget_destroy(GTK_WIDGET(parent_window));
}


void ajouter_nouveau_ut(GtkWidget *widget, gpointer data) {
    GtkBuilder *builder;
    GtkEntry *user;
    GtkEntry *password;
    GtkEntry *role_c;

    builder = gtk_builder_new();
    if (!gtk_builder_add_from_resource(builder, "/com/gec/saifeddine/ajout_ut_diag.glade", NULL)) {
        printf("Failed to initialize ajout_ut_diag.glade\n");
        return;
    }

    user = GTK_ENTRY(gtk_builder_get_object(builder, "user"));
    password = GTK_ENTRY(gtk_builder_get_object(builder, "pass"));
    role_c = GTK_ENTRY(gtk_builder_get_object(builder, "role_entry"));
    getElementsNew * elem2 = (getElementsNew *) data;
    getElementsNew * elem = g_new(getElementsNew,3);
    elem->builder = builder;
    elem->nodeUsers =elem2->nodeUsers;
    elem->builder2 = elem2->builder2;
    gtk_widget_set_name(GTK_WIDGET(user),"inputes");
gtk_widget_set_name(GTK_WIDGET(password),"inputes");
gtk_widget_set_name(GTK_WIDGET(role_c),"inputes");
    GtkButton *submit_button = GTK_BUTTON(gtk_builder_get_object(builder, "submit_add"));
    gtk_widget_set_name(GTK_WIDGET(submit_button),"buttonsDash");
    load_css(submit_button,"styles.css","buttonsDash");

    load_css(user,"styles.css","inputes");

    load_css(password,"styles.css","inputes");

    load_css(role_c,"styles.css","inputes");


    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_add_user_submit), elem);

    GtkWindow *window = GTK_WINDOW(gtk_builder_get_object(builder, "add_ut"));
    gtk_window_set_modal(GTK_WINDOW(window), TRUE);
    gtk_widget_show_all(GTK_WIDGET(window));
}





ReceiptNodes createReceiptNode(const char *receiptContent) {
    ReceiptNodes newNode = (ReceiptNodes)malloc(sizeof(ReceiptNode));
    if (newNode == NULL) {
        perror("Failed to allocate memory for new receipt node");
        exit(EXIT_FAILURE);
    }
    newNode->receipt = strdup(receiptContent);
    if (newNode->receipt == NULL) {
        perror("Failed to allocate memory for receipt content");
        free(newNode);
        exit(EXIT_FAILURE);
    }
    newNode->next = NULL;
    return newNode;
}

void disable_visible_notebook_tab(GtkWidget *notebook, int page_num) {
    GtkNotebook *notebookd = GTK_NOTEBOOK(notebook);
    GtkWidget *child = gtk_notebook_get_nth_page(notebookd, page_num);
    gtk_notebook_set_tab_reorderable(notebookd, child, FALSE);
}

void readFromFileReceipt(const char *filename, ReceiptNodes *main_node) {
    FILE *readFile = fopen(filename, "r");
    char buffer[MAX_LINE_LENGTH];
    char receipt[MAX_LINE_LENGTH * 200];
    int in_receipt = 0;

    if (readFile == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    receipt[0] = '\0';
    while (fgets(buffer, sizeof(buffer), readFile) != NULL) {
        if (strstr(buffer, "---------- Liste des Produits Achetes ----------")) {
            if (in_receipt) {
                receipt[0] = '\0';
            }
            in_receipt = 1;
            strcat(receipt, buffer);
        } else if (strstr(buffer, "---------- Fin des produits Achetes-----------------")) {
            if (in_receipt) {
                strcat(receipt, buffer);
                ReceiptNodes newNode = createReceiptNode(receipt);
                newNode->next = *main_node;
                *main_node = newNode;
                receipt[0] = '\0';
                in_receipt = 0;
            }
        } else if (in_receipt) {
            strcat(receipt, buffer);
        }
    }

    fclose(readFile);
}

void get_current_time(char *buffer, size_t buffer_size) {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, buffer_size, "%Y-%m-%d %H:%M:%S", timeinfo);
}






void iterate_columns_data(GtkTreeView *treeview, GtkBuilder * builder,getData * data) {
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    GtkTreeIter iter;
    gboolean valid;

    if (gtk_tree_model_get_n_columns(model) < 4) {
        g_warning("The model does not have four columns.");
        return;
    }

    GtkWidget *NoteBook;
    GtkLabel * total_sum;
    GtkLabel * rendu;
    GtkEntry * mont;
    GtkTreeView * rec_tree;
    GtkListStore *rec_store;
    NoteBook= GTK_NOTEBOOK(gtk_builder_get_object(builder,"noteMain"));
    total_sum= GTK_LABEL(gtk_builder_get_object(builder,"total_sum"));
    rendu= GTK_LABEL(gtk_builder_get_object(builder,"rendu"));
    mont= GTK_ENTRY(gtk_builder_get_object(builder,"montant"));
    rec_tree = GTK_TREE_VIEW(gtk_builder_get_object(builder,"rec_tree"));
    rec_store = GTK_LIST_STORE(gtk_tree_view_get_model(rec_tree));



    valid = gtk_tree_model_get_iter_first(model, &iter);
    FILE * recFile;
    recFile = fopen("recettes.csv","a+");
    char buffer[80];
    get_current_time(buffer,sizeof(buffer));

    gchar * total = gtk_label_get_text(total_sum);
    gchar * renduS = gtk_label_get_text(rendu);
     fprintf(recFile,"---------- Liste des Produits Achetes ----------\n \n--------DATE: %s--------\n-----------TOTAL: %s DT ----------- \n-------------- RENDU: %s DT --------------\n --------VENDEUR: %s -----------\n",buffer,total,renduS,userG);
    while (valid) {
        gchar *value1, *value2, *value3, *value4;

        gtk_tree_model_get(model, &iter, 0, &value1, 1, &value2, 2, &value3, 3, &value4, -1);

        fprintf(recFile,">>Quantite: %s Produit: %s Prix Unitaire: %s Prix Total: %s >>\n" , value1,value2,value3,value4);
        int newquantVal = _strtoi64(data->q,NULL,NULL) - _strtoi64(value1,NULL,NULL);
        char bufferQuantity[50];
        sprintf(bufferQuantity,"%d",newquantVal);

        g_free(value1);
        g_free(value2);
        g_free(value3);
        g_free(value4);

        valid = gtk_tree_model_iter_next(model, &iter);
    }
    fprintf(recFile,"---------- Fin des produits Achetes-----------------\n");
    fclose(recFile);

    GtkListStore *list_store = GTK_LIST_STORE(model);
    gtk_list_store_clear(list_store);
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(model));
    int i =0;
    gchar bufferS[80];
    gtk_list_store_clear(rec_store);
    ReceiptNodes  head = NULL;
    readFromFileReceipt("recettes.csv", &head);

    ReceiptNodes current = head;

    while (current != NULL) {
        sprintf(bufferS,"%d",i);
        i++;
        addProductsRec(rec_tree,rec_store,current->receipt,bufferS);
        printf("%s", current->receipt);
        current = current->next;

    }


    gtk_tree_view_set_model(rec_tree,GTK_TREE_MODEL(rec_store));
     int  itemsCount = getItemsCount(treeview);
    if (itemsCount == 0) {
        disable_notebook_tab(GTK_NOTEBOOK(NoteBook),2);
    }
    gtk_entry_set_text(mont,"");
    gtk_label_set_text(rendu,"0.0");
    gtk_label_set_text(total_sum,"0.0");
}


void handleMontant(GtkEditable * entryMontant , gpointer data)
{
    getWidget * instance_data = (getWidget *) data;
    GtkLabel * total;
    GtkButton * caisse_bt;
    GtkLabel * rendu;
    total = GTK_LABEL(gtk_builder_get_object(instance_data->builder,"total_sum"));
    caisse_bt = GTK_BUTTON(gtk_builder_get_object(instance_data->builder,"proc_caisse"));
    rendu = GTK_LABEL(gtk_builder_get_object(instance_data->builder,"rendu"));

    gchar * getMontant = gtk_entry_get_text(GTK_ENTRY(entryMontant));
    if(strtof(getMontant,NULL) < strtof(gtk_label_get_text(total),NULL))
    {
        gtk_widget_set_sensitive(caisse_bt, FALSE);
        gtk_label_set_text(rendu,"0");
    }else  if (strtof(getMontant,NULL) >= strtof(gtk_label_get_text(total),NULL)){
        gtk_widget_set_sensitive(caisse_bt, TRUE);
        char buffer[50];
        sprintf(buffer,"%.2f", strtof(getMontant,NULL) - strtof(gtk_label_get_text(total),NULL));
        gtk_label_set_text(rendu,buffer);

    }
    if(strtof(getMontant,NULL) <=0){
        gtk_entry_set_text(GTK_ENTRY(entryMontant), "");
    }
}



void disable_notebook_tab(GtkNotebook *notebook, gint page_num) {

    GtkWidget *child = gtk_notebook_get_nth_page(notebook, page_num);
    if (child) {
        gtk_widget_set_sensitive(child, FALSE);
    }
}

void enable_notebook_tab(GtkNotebook *notebook, gint page_num) {

    GtkWidget *child = gtk_notebook_get_nth_page(notebook, page_num);
    if (child) {
        gtk_widget_set_sensitive(child, TRUE);
    }
}
int getItemsCount(GtkTreeView *treeView) {
    GtkTreeModel *model = gtk_tree_view_get_model(treeView);
    if (model == NULL) {
        return 0;
    }

    int count = gtk_tree_model_iter_n_children(model, NULL);

    return count;
}

void handleCaissePress(GtkWidget * widget , gpointer data)
{
    getWidget * instance_data = (getWidget*) data;
    GtkTreeView * caisseTreeView;
    caisseTreeView = GTK_TREE_VIEW(gtk_builder_get_object(instance_data->builder,"les_items_caisse"));
    iterate_columns_data(caisseTreeView, instance_data->builder,instance_data);

}


gboolean update_products(gpointer data) {

    ReceiptNodes recherchedata = (ReceiptNodes )data;


    readFromFileReceipt("recettes.csv",&recherchedata);


    return TRUE;
}


void load_css(GtkWidget *widget, const gchar *filename, const gchar *className)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkScreen *screen = gtk_widget_get_screen(widget);

    if (!gtk_css_provider_load_from_path(provider, filename, NULL))
    {
        g_printerr("Error loading CSS file: %s\n", filename);
        g_object_unref(provider);
        return;
    }

    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_class(context, className);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
}

void removeFirstChar(char *str)
{
    int j = 0;
    for (int i = 1; str[i] != '\0'; i++)
    {
        str[j++] = str[i];
    }
    str[j] = '\0';
}


int wordCount(char  * text, char sep)
{
    int lengthT = length(text);
    int wordCount = 0;
    for(int i =0; i < lengthT ; i++)
    {
        if(text[i] == sep)
        {
            wordCount++;
        }
    }
    return wordCount +1;
}


int length(char * text)
{
    int i =0 ;
    while(text[i] != '\0')
    {
        i++;

    }
    return i;
}

char * sanitize_string(char * line, char sep)
{
    int lengtht = length(line);
    line[lengtht] = sep;
    line[lengtht+1] = '\0';
    return line;
}

char ** splitText(char * text, char sep )
{
    char * aux;
    char ** strings;


    sanitize_string(text,',');

    int lengthT = length(text);

    int count = wordCount(text, sep);
    sanitize_string(text,sep);
    int auxCount = 0;
    int stringsCount = 0;



    aux = (char*)malloc((lengthT +1)*sizeof(char));
    strings = (char**)malloc((count+1) * sizeof(char*));
    if(aux == NULL)
    {
        printf("Allocation of memory failed");
    }

    if(strings == NULL)
    {
        printf("Allocation of memory failed");
    }

    for(int i = 0; i <= count ; i++)
    {
        strings[i] = (char*)malloc(sizeof(char) * (lengthT + 1));
        if(strings[i] == NULL)
            printf("Memory allocation failed");
    }
    if(count == 1)
    {

    }
    else
    {
        for(int i =0; text[i]; i++)
        {
            aux[auxCount] = text[i];
            if(text[i] == sep || text[i] == '\0')
            {
                aux[auxCount] = '\0';
                strcpy(strings[stringsCount],aux);
                if(stringsCount >= 1)
                {
                    removeFirstChar(strings[stringsCount]);
                }
                auxCount = 0;
                stringsCount++;

            }

            auxCount++;

        }

    }

    return strings;

}

void readFromFile(const char * filename, productNode main_node)
{
    FILE * readFile = fopen(filename, "r");
    char buffer[256];

    if (readFile == NULL)
    {
        printf("Error opening file %s\n", filename);

    }
    while(fgets(buffer, sizeof(buffer), readFile) != NULL)
    {
        char ** split = splitText(sanitize_string(buffer,','),',');
        if (split && split[4] != NULL) {
            Product tempProd;
            strcpy(tempProd.productName, split[0]);
            strcpy(tempProd.productDescription, split[1]);
            strcpy(tempProd.productPrice, split[2]);
            strcpy(tempProd.productQuantity, split[3]);
            strcpy(tempProd.productRef, split[4]);
            productNode tempNode = createProduct(tempProd);
            main_node->next = tempNode;
            main_node = main_node->next;
            free(split);
        } else {

            printf("Malformed line in file %s: %s\n", filename, buffer);

        }

    }
    fclose(readFile);

}
char *trim(char *str) {
    // Trim leading whitespace
    while (isspace((unsigned char)*str))
        str++;
    if (*str == 0) // All spaces?
        return str;

    // Trim trailing whitespace
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    // Write new null terminator
    *(end + 1) = '\0';

    return str;
}

int readFromFileUsers(const char *filename, const char *user, const char *password, usersNode *Users) {
    FILE *readFile = fopen(filename, "r");
    char buffer[256];

    if (readFile == NULL) {
        printf("Error opening file %s\n", filename);
        return 0;
    }

    usersNode current = NULL;

    int userFound = 0;

    while (fgets(buffer, sizeof(buffer), readFile) != NULL) {
        char **split = splitText(sanitize_string(buffer, ','), ',');
        if (split != NULL) {
            usersNode newNode = malloc(sizeof(userNode));
            if (newNode == NULL) {
                printf("Memory allocation error\n");
                fclose(readFile);
                free(split[0]);
                free(split);
                return 0;
            }

            strcpy(newNode->user.UserName, trim(split[0]));
            strcpy(newNode->user.Password, trim(split[1]));
            strcpy(newNode->user.Role, trim(split[2]));
            newNode->next = NULL;

            if (*Users == NULL) {
                *Users = newNode;
            } else {
                current->next = newNode;
            }
            current = newNode;

            if (strcmp(trim(split[0]), user) == 0 && strcmp(trim(split[1]), password) == 0) {
                if (strcasecmp(trim(split[2]), "admin") == 0) {
                    userFound = 1;
                } else if (strcasecmp(trim(split[2]), "emp") == 0) {
                    userFound = 2;
                }
            }

            free(split[0]); // Freeing the duplicated string
            free(split);
        }
    }

    fclose(readFile);
    return userFound;
}


void handleAddProduct(GtkWidget *widget, gpointer data)
{
    fieldsData *newFields = (fieldsData*) data;
    const gchar *nom = gtk_entry_get_text(GTK_ENTRY(newFields->nom));
    const gchar *desc = gtk_entry_get_text(GTK_ENTRY(newFields->desc));
    const gchar *prix = gtk_entry_get_text(GTK_ENTRY(newFields->prix));
    const gchar *quantite = gtk_entry_get_text(GTK_ENTRY(newFields->quant));
    const gchar *ref = gtk_entry_get_text(GTK_ENTRY(newFields->ref));
    gchar message[256];
    GtkWidget *newErrorDiag;


    if (strcmp(nom, "") == 0)
    {
        strcpy(message, "Le nom ne doit pas être vide");
        newErrorDiag = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
        gtk_dialog_run(GTK_DIALOG(newErrorDiag));
        gtk_widget_destroy(newErrorDiag);
        return;
    }

    if (strcmp(desc, "") == 0)
    {
        strcpy(message, "La description ne doit pas être vide");
        newErrorDiag = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
        gtk_dialog_run(GTK_DIALOG(newErrorDiag));
        gtk_widget_destroy(newErrorDiag);
        return;
    }

    if (strcmp(prix, "") == 0)
    {
        strcpy(message, "Le prix ne doit pas être vide");
        newErrorDiag = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
        gtk_dialog_run(GTK_DIALOG(newErrorDiag));
        gtk_widget_destroy(newErrorDiag);
        return;
    }

    if (strcmp(quantite, "") == 0)
    {
        strcpy(message, "La quantite ne doit pas être vide");
        newErrorDiag = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
        gtk_dialog_run(GTK_DIALOG(newErrorDiag));
        gtk_widget_destroy(newErrorDiag);
        return;
    }

    if (strcmp(ref, "") == 0)
    {
        strcpy(message, "La reference ne doit pas être vide");
        newErrorDiag = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
        gtk_dialog_run(GTK_DIALOG(newErrorDiag));
        gtk_widget_destroy(newErrorDiag);
        return;
    }


    gboolean validQuantity = TRUE;
    for (int i = 0; quantite[i] != '\0'; i++)
    {
        if (!isdigit(quantite[i]))
        {
            validQuantity = FALSE;
            break;
        }
    }

    if (!validQuantity)
    {
        strcpy(message, "La quantite doit etre un valeur numeric");
        newErrorDiag = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
        gtk_dialog_run(GTK_DIALOG(newErrorDiag));
        gtk_widget_destroy(newErrorDiag);
        return;
    }


    if (strtol(quantite, NULL, 10) <= 0)
    {
        strcpy(message, "La quantite doit etre un entier positif");
        newErrorDiag = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
        gtk_dialog_run(GTK_DIALOG(newErrorDiag));
        gtk_widget_destroy(newErrorDiag);
        return;
    }


    char *endptr;
    float price = strtof(prix, &endptr);

    if (*endptr != '\0')
    {
        strcpy(message, "Le prix doit etre un valeur numeric");
        newErrorDiag = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
        gtk_dialog_run(GTK_DIALOG(newErrorDiag));
        gtk_widget_destroy(newErrorDiag);
        return;
    }

    if (price < 0)
    {
        strcpy(message, "Le prix doit etre positif");
        newErrorDiag = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
        gtk_dialog_run(GTK_DIALOG(newErrorDiag));
        gtk_widget_destroy(newErrorDiag);
        return;
    }

    gchar newProduct[256];
    strcpy(newProduct,nom);
    strcat(newProduct,",");
    strcat(newProduct,desc);
    strcat(newProduct,",");
    strcat(newProduct,prix);
    strcat(newProduct,",");
    strcat(newProduct,quantite);
    strcat(newProduct,",");
    strcat(newProduct,ref);
    strcat(newProduct,"\n");


    FILE *file = fopen("hf.csv", "a");

    if (file == NULL)
    {
        strcpy(message, "Le fichier est introuvable");
        newErrorDiag = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
        gtk_dialog_run(GTK_DIALOG(newErrorDiag));
        gtk_widget_destroy(newErrorDiag);
        return;
    }




    fprintf(file, newProduct);


    addProducts(newFields->recherchedata->rech1->treeview,newFields->recherchedata->rech1->newListStore,nom , desc, prix, quantite, ref);
    addProducts(newFields->recherchedata->rech2->treeview,newFields->recherchedata->rech2->newListStore,nom , desc, prix, quantite, ref);
    gtk_widget_destroy(GTK_WIDGET(newFields->prodAddWindow));
    fclose(file);


}




void addProduitNouveau(GtkWidget * widget,  gpointer data)
{
    rechercheData * info = (rechercheData*) data;
    GtkBuilder * addProdBuild = gtk_builder_new();
    GtkButton * ajout_prod_conf;
    GtkWindow * addProdWindow;
    GError *error = NULL;
    fieldsData * newFieldsData = g_new(fieldsData,5);

    if(!gtk_builder_add_from_resource(addProdBuild,"/com/gec/saifeddine/addprod.glade", &error))
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    addProdWindow = GTK_WINDOW(gtk_builder_get_object(addProdBuild,"addProdWindow"));
    ajout_prod_conf = GTK_BUTTON(gtk_builder_get_object(addProdBuild,"ajout_prod_conf"));

    newFieldsData->nom = GTK_ENTRY(gtk_builder_get_object(addProdBuild,"nomprod"));
    newFieldsData->desc = GTK_ENTRY(gtk_builder_get_object(addProdBuild,"descprod"));
    newFieldsData->prix = GTK_ENTRY(gtk_builder_get_object(addProdBuild,"prixprod"));
    newFieldsData->quant = GTK_ENTRY(gtk_builder_get_object(addProdBuild,"quantiteprod"));
    newFieldsData->ref = GTK_ENTRY(gtk_builder_get_object(addProdBuild,"refprod"));
    newFieldsData->recherchedata = info;
    newFieldsData->prodAddWindow = addProdWindow;

    g_signal_connect(ajout_prod_conf,"clicked",G_CALLBACK(handleAddProduct), newFieldsData);




    gtk_widget_set_name(GTK_WIDGET(ajout_prod_conf), "buttonsDash");
    load_css(ajout_prod_conf, "styles.css",  "buttonsDash");




    if (addProdWindow == NULL)
    {
        g_printerr("Error: addProdWindow is NULL. Ensure the window ID is correct in the glade file.\n");
        return;
    }

    gtk_widget_show_all(GTK_WIDGET(addProdWindow));

    gtk_main();
    g_signal_connect(addProdWindow, "destroy", G_CALLBACK(on_window_destroy), NULL);
}

void handleSelectedProd(GtkTreeSelection * selected_prod, gpointer data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    getWidget * widgetList = (getWidget*) data;
    gint * nb_items = (int*)malloc(sizeof(int));
    gchar * name, *desc, *prix, *quantity,* ref;


    if(gtk_tree_selection_get_selected(selected_prod, &model, &iter))
    {
        gtk_widget_set_sensitive(widgetList->getButton,TRUE);
        gtk_tree_model_get(model, &iter,0, &name,-1);
        gtk_tree_model_get(model, &iter,1, &desc,-1);
        gtk_tree_model_get(model, &iter,2, &prix,-1);
        gtk_tree_model_get(model, &iter,3, &quantity,-1);
        gtk_tree_model_get(model, &iter,4, &ref,-1);
        getData  * prodData = g_new(getData,8);
        prodData->n = name;
        prodData->d = desc;
        prodData->p = prix;
        prodData->q = quantity;
        prodData->r = ref;
        prodData->getProcCaisse = widgetList->getButton2;
        prodData->label = widgetList->label;
        prodData->builder = widgetList->builder;



        g_signal_connect(widgetList->getButton,"clicked",G_CALLBACK(ajoutDansLaCaisse), prodData);
    }
    else
    {
        gtk_widget_set_sensitive(widgetList->getButton,FALSE);
    }
}


void supprProd(GtkWidget *widget, gpointer data) {
    getData *getInfo = (getData *)data;
    gchar buffer[360];
    gchar bufferFile[360];
  GtkDialog * dialog;
     strcpy(buffer, getInfo->n);
    strcat(buffer, ",");
    strcat(buffer, getInfo->d);
    strcat(buffer, ",");
    strcat(buffer, getInfo->p);
    strcat(buffer, ",");
    strcat(buffer, getInfo->q);
    strcat(buffer, ",");
    strcat(buffer, getInfo->r);


    FILE *newFile;
    FILE *tempFile;

    tempFile = fopen("hf.csv.tmp", "w");
    if (!tempFile) {
        perror("Unable to open temporary file");
        return;
    }

    newFile = fopen("hf.csv", "r");
    if (!newFile) {
        perror("Unable to open original file");
        fclose(tempFile);
        return;
    }

    gboolean line_removed = FALSE;


    while (fgets(bufferFile, sizeof(bufferFile), newFile)) {
        if (strcmp(buffer, bufferFile) != 0) {
            fputs(bufferFile, tempFile);
        } else {
            line_removed = TRUE;
        }
    }

    fclose(newFile);
    fclose(tempFile);

    if (line_removed) {

        if (remove("hf.csv") != 0) {
            perror("Error deleting the original file");
            return;
        }
        if (rename("hf.csv.tmp", "hf.csv") != 0) {
            perror("Error renaming the temporary file");
            return;
        }
    } else {

        remove("hf.csv.tmp");
    }


    if (gtk_tree_selection_get_selected(getInfo->selection, &(getInfo->model), &(getInfo->iter))) {
        gtk_list_store_remove(GTK_LIST_STORE(getInfo->model), &(getInfo->iter));

        dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", "La produit a été supprimé avec succés");
        gtk_dialog_run(dialog);
        gtk_widget_destroy(dialog);
         gtk_tree_selection_unselect_all(getInfo->selection);


    }
}

void handleSelectedProdSuppr(GtkTreeSelection * selected_prod, gpointer data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    getWidget * widgetList = (getWidget*) data;
    gint * nb_items = (int*)malloc(sizeof(int));
    gchar * name, *desc, *prix, *quantity,* ref;


    if(gtk_tree_selection_get_selected(selected_prod, &model, &iter))
    {
        gtk_widget_set_sensitive(widgetList->getButton,TRUE);
        gtk_tree_model_get(model, &iter,0, &name,-1);
        gtk_tree_model_get(model, &iter,1, &desc,-1);
        gtk_tree_model_get(model, &iter,2, &prix,-1);
        gtk_tree_model_get(model, &iter,3, &quantity,-1);
        gtk_tree_model_get(model, &iter,4, &ref,-1);
        getData  * prodData = g_new(getData,5);
        prodData->n = name;
        prodData->d = desc;
        prodData->p = prix;
        prodData->q = quantity;
        prodData->r = ref;
        prodData->iter = iter;
        prodData->model = model;
        prodData->selection = selected_prod;
        prodData->Node = widgetList->Node;

        g_signal_connect(widgetList->getButton,"clicked",G_CALLBACK(supprProd), prodData);
    }
    else
    {
        gtk_widget_set_sensitive(widgetList->getButton,FALSE);
    }
}


void listProduitsGetSelected(GtkTreeView * listProd, getWidget *Widget)
{
    GtkTreeSelection * selected_prod;
    selected_prod = gtk_tree_view_get_selection(GTK_TREE_VIEW(listProd));
    g_signal_connect(selected_prod,"changed",G_CALLBACK(handleSelectedProd),Widget);
}

void listProduitsGetSelectedStock(GtkTreeView * listProd, getWidget *Widget)
{
    GtkTreeSelection * selected_prod;
    selected_prod = gtk_tree_view_get_selection(GTK_TREE_VIEW(listProd));
    g_signal_connect(selected_prod,"changed",G_CALLBACK(handleSelectedProdSuppr),Widget);
}


