#include "gec_caisse_functions.h"




void on_window_destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

void Dashboard(GtkBuilder * mainDashBoard, usersNode Users )
{
    GtkWindow * window;
    GError *error = NULL;

    GtkListStore * listStoreProd;
    GtkListStore * caisseStore;
    GtkTreeView * listProd;
    GtkTreeView * gesstock;
    GtkListStore * rec_store;
    GtkTreeView * rec_tree;
    GtkTreeView * users_tree;
    GtkListStore * users_store;


    GtkVBox* add_ut_scroll;
    GtkHBox * content_ut_tree;

    GtkTreeView * caisse_container_items;




    GtkListStore * listStoreProdStock;
   GtkVButtonBox * containergessstock;


    GtkButton *ajout_caisse;
    GtkButton * caisse;
    GtkButton * ajout_prod;
    GtkButton * proc_caisse;
    GtkButton * suppr_element_caisse;

    GtkButton * bt1;
    GtkButton * bt2;
    GtkButton * bt3;
    GtkButton * bt4;
    GtkButton * bt5;
    GtkButton * bt6;
    GtkButton * bt7;
    GtkButton * bt8;
    GtkButton * bt9;
    GtkButton * bt0;


    GtkButton * checkout;
    GtkButton * suppr_prod;
    GtkWidget * mainGrid;
    GtkVBox * containerWidget;
    GtkWidget * NoteBook;
    GtkHPaned * container_rec;
    GtkHPaned * containerut;
    GtkButton * ajout_utilisateur;



    GtkEntry *recherche_entry;
    GtkEntry *recherche2;
    GtkEntry * montant;
    GtkEntry * vendeur;
    GtkEntry * recherche_ut;
    GtkLabel * labelTotal;

    GtkScrolledWindow * containerProd;
    GtkHBox * containerCaisse;
    GtkScrolledWindow * caisse_tree_scroll;
    GtkScrolledWindow * tree_rec_container;
    GtkHButtonBox * containerProdSTOCK;
    GtkHButtonBox * numpadBox;
    GtkVButtonBox * textContainerCaisse;
    GtkHButtonBox * hbuttonCaisse;

    GtkHButtonBox * recherche_box;
    GtkVButtonBox * containerItemsStock;
    GtkHButtonBox * vendeur_input;
    GtkButton * supprtouscaisse;



    GtkLabel * total_pro;
    GtkVButtonBox* containerItems;
    gchar sumOfProdChar[50];




    usersNode CurrentUsers = Users;


    gint sumOfProducts = 0;
    gchar * customLabel = "Totale des produits: ";

    ReceiptNodes main_node = NULL;
     readFromFileReceipt("recettes.csv", &main_node);




    Product firstProd;
    strcpy(firstProd.productName,"Init");
    strcpy(firstProd.productDescription,"Init");
    strcpy(firstProd.productPrice,"0.0");
    strcpy(firstProd.productQuantity,"0");
    strcpy(firstProd.productRef,"init");

    productNode mainNodes = createProduct(firstProd);
    readFromFile("hf.csv",mainNodes);

    window = GTK_WINDOW(gtk_builder_get_object(mainDashBoard,"dashboard"));
    listProd = GTK_TREE_VIEW(gtk_builder_get_object(mainDashBoard,"listprod"));
    ajout_caisse = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"addtocart"));


    total_pro = GTK_LABEL(gtk_builder_get_object(mainDashBoard, "total_pro"));
    recherche_entry = GTK_ENTRY(gtk_builder_get_object(mainDashBoard,"recherche"));
    containerItems = GTK_VBUTTON_BOX(gtk_builder_get_object(mainDashBoard,"vbuttonbox2"));
    ajout_prod = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"addprod"));

    checkout = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"checkout"));
    mainGrid = GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"mainGridWin"));
    gesstock = GTK_TREE_VIEW(gtk_builder_get_object(mainDashBoard, "gesstock"));
    recherche2= GTK_ENTRY(gtk_builder_get_object(mainDashBoard, "recherche2"));
    vendeur = GTK_ENTRY(gtk_builder_get_object(mainDashBoard, "vendeur"));
    containerProd = GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"scrolledwindow1"));
    recherche_box = GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"hbuttonbox4"));
    hbuttonCaisse= GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"hbuttonboxCaisse"));
    containerProdSTOCK = GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"containerProdStock"));
    containerItemsStock = GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"containerItemsStock"));
    numpadBox = GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"numpad"));
    suppr_prod = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"supprprod"));
    containerWidget =  GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"containerWidg"));
    containergessstock =  GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"containergessstock"));
    container_rec =  GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"container_rec"));
    containerCaisse =  GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"containerCaisse"));
    caisse_container_items = GTK_TREE_VIEW(gtk_builder_get_object(mainDashBoard,"les_items_caisse"));
    proc_caisse = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"proc_caisse"));
    labelTotal = GTK_LABEL(gtk_builder_get_object(mainDashBoard,"total_sum"));
    montant =  GTK_ENTRY(gtk_builder_get_object(mainDashBoard, "montant"));
    NoteBook = GTK_NOTEBOOK(gtk_builder_get_object(mainDashBoard,"noteMain"));
    rec_tree = GTK_TREE_VIEW(gtk_builder_get_object(mainDashBoard,"rec_tree"));
     supprtouscaisse = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"supprtous"));
     ajout_utilisateur = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"ajout_ut"));
    suppr_element_caisse = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"supprunelem"));
    textContainerCaisse = GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"textContainerCaisse"));
    caisse_tree_scroll = GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"caisse_tree_scroll"));
    tree_rec_container = GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"rec_tree_container"));
    vendeur_input = GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"vendeur_input"));
    users_tree = GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"users_tree"));
    add_ut_scroll = GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"containerut"));
    content_ut_tree = GTK_WIDGET(gtk_builder_get_object(mainDashBoard,"ut_table"));
    recherche_ut = GTK_ENTRY(gtk_builder_get_object(mainDashBoard,"recherche_ut"));



     bt1 = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"1bt"));
     bt2 = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"2bt"));
     bt3 = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"3bt"));
     bt4 = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"4bt"));
     bt5 = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"5bt"));
     bt6 = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"6bt"));
     bt7 = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"7bt"));
     bt8 = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"8bt"));
     bt9 = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"9bt"));
     bt0 = GTK_BUTTON(gtk_builder_get_object(mainDashBoard,"0bt"));


     g_signal_connect(bt0,"clicked",G_CALLBACK(increment_to_montant1) ,mainDashBoard );
     g_signal_connect(bt1,"clicked",G_CALLBACK(increment_to_montant2) ,mainDashBoard );
     g_signal_connect(bt2,"clicked",G_CALLBACK(increment_to_montant3) ,mainDashBoard );
     g_signal_connect(bt3,"clicked",G_CALLBACK(increment_to_montant4) ,mainDashBoard );
     g_signal_connect(bt4,"clicked",G_CALLBACK(increment_to_montant5) ,mainDashBoard  );
     g_signal_connect(bt5,"clicked",G_CALLBACK(increment_to_montant6) ,mainDashBoard  );
     g_signal_connect(bt6,"clicked",G_CALLBACK(increment_to_montant7) ,mainDashBoard  );
     g_signal_connect(bt7,"clicked",G_CALLBACK(increment_to_montant8) ,mainDashBoard  );
     g_signal_connect(bt8,"clicked",G_CALLBACK(increment_to_montant9) ,mainDashBoard  );
     g_signal_connect(bt9,"clicked",G_CALLBACK(increment_to_montant10) ,mainDashBoard  );




    gtk_widget_set_sensitive(GTK_WIDGET(ajout_caisse),FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(suppr_prod),FALSE);
    disable_notebook_tab(GTK_NOTEBOOK(NoteBook),2);


    getElementsNew * elem = g_new(getElementsNew,5);
    elem->builder2 = mainDashBoard;
    elem->nodeUsers = CurrentUsers;
    elem->tree = users_tree;
    elem->store = GTK_LIST_STORE(users_store);
    g_signal_connect(checkout,"clicked",G_CALLBACK(navToCaisse),NoteBook);
    g_signal_connect(ajout_utilisateur,"clicked",G_CALLBACK(ajouter_nouveau_ut),elem);
    start_timer(elem);


    rechercheData *recherchedata = g_new(rechercheData,2);
    rechercheData *recherchedata2 = g_new(rechercheData,2);
    rechercheData * recherchedata3 = g_new(rechercheData,2);
    rechercheData * recherchedata4 = g_new(rechercheData,2);

    listStoreProd = gtk_list_store_new(5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    addColumns("Nom", listProd, 0);
    addColumns("Description", listProd, 1);
    addColumns("Prix", listProd, 2);
    addColumns("Quantite", listProd, 3);
    addColumns("Reference", listProd, 4);
    gtk_tree_view_set_model(listProd,GTK_TREE_MODEL(listStoreProd));




    listStoreProdStock = gtk_list_store_new(5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    addColumns("Nom", gesstock, 0);
    addColumns("Description", gesstock, 1);
    addColumns("Prix", gesstock, 2);
    addColumns("Quantite", gesstock, 3);
    addColumns("Reference", gesstock, 4);
    gtk_tree_view_set_model(gesstock,GTK_TREE_MODEL(listStoreProdStock));

    users_store = gtk_list_store_new(3,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
    addColumns("Utilisateur", users_tree,0);
    addColumns("Mot de passe", users_tree,1);
    addColumns("Role", users_tree,2);
    gtk_tree_view_set_model(users_tree,GTK_TREE_MODEL(users_store));

    caisseStore = gtk_list_store_new(4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    addColumns("Quantite",caisse_container_items,0);
    addColumns("Produit",caisse_container_items,1);
    addColumns("Prix Unitaire",caisse_container_items,2);
    addColumns("Prix Totale",caisse_container_items,3);
    gtk_tree_view_set_model(caisse_container_items,GTK_TREE_MODEL(caisseStore));

    rec_store = gtk_list_store_new(2,G_TYPE_STRING, G_TYPE_STRING);
    addColumns("Recettes",rec_tree,0);
    addColumns("Id",rec_tree,1);
    gtk_tree_view_set_model(rec_tree,GTK_TREE_MODEL(rec_store));


    ReceiptNodes current = main_node;
    headG = main_node;
    gint i =0;
    gchar buffer[80];
    while (current != NULL) {
        sprintf(buffer,"%d",i);

        addProductsRec(rec_tree,rec_store,current->receipt,buffer);

        current = current->next;
        i++;
    }






 int itemsCount = getItemsCount(caisse_container_items);
CAISSE_LISTSTORE = caisseStore;

if(itemsCount == 0)
{
    gtk_widget_set_sensitive(proc_caisse,FALSE);
}


    usersNode currusers = Users;

    recherchedata2->mainNode = mainNodes;
    recherchedata2->newListStore = listStoreProdStock;
    recherchedata2->treeview = gesstock;
    g_signal_connect(recherche2, "changed",G_CALLBACK(recherche_produits), recherchedata2);


    recherchedata->mainNode = mainNodes;
    recherchedata->newListStore = listStoreProd;
    recherchedata->treeview = listProd;
    g_signal_connect(recherche_entry, "changed",G_CALLBACK(recherche_produits), recherchedata);

    ReceiptNodes another = main_node;
    recherchedata3->receiptNode = headG;
    recherchedata3->newListStore = rec_store;
    recherchedata3->treeview = rec_tree;

     g_signal_connect(vendeur, "changed",G_CALLBACK(recherche_vendeur), recherchedata3);


     recherchedata4->users = currusers;
     recherchedata4->treeview = users_tree;
     recherchedata4->newListStore = users_store;

     g_signal_connect(recherche_ut, "changed",G_CALLBACK(recherche_utd), recherchedata4);

    g_signal_connect(supprtouscaisse,"clicked",G_CALLBACK(supprtouscaisseFunc),mainDashBoard);
    GtkTreeSelection * selectionCaisse;
    selectionCaisse = gtk_tree_view_get_selection(caisse_container_items);
    g_signal_connect(selectionCaisse,"changed",G_CALLBACK(on_selected_caisse_item),mainDashBoard );


    while(mainNodes->next!= NULL)
    {
        addProducts(listProd, listStoreProd, mainNodes->next->product.productName, mainNodes->next->product.productDescription, mainNodes->next->product.productPrice, mainNodes->next->product.productQuantity, mainNodes->next->product.productRef);
        addProducts(gesstock, listStoreProdStock, mainNodes->next->product.productName, mainNodes->next->product.productDescription, mainNodes->next->product.productPrice, mainNodes->next->product.productQuantity, mainNodes->next->product.productRef);
        sumOfProducts += (_strtoi64(mainNodes->next->product.productQuantity,NULL,NULL));
        mainNodes = mainNodes->next;

    }

   //g_signal_connect(listProd, "focus-in-event", G_CALLBACK(remove_selections),NULL);


    getWidget  * mainDashButtons =g_new(getWidget,5);
    mainDashButtons->getButton = GTK_WIDGET(ajout_caisse);
    mainDashButtons->getButton2 = GTK_BUTTON(proc_caisse);
    mainDashButtons->builder = mainDashBoard;
    mainDashButtons->label = labelTotal;
    mainDashButtons->builder = mainDashBoard;

    getWidget  * mainDashButtonsStock =g_new(getWidget,2);
    mainDashButtonsStock->getButton = GTK_WIDGET(suppr_prod);
    mainDashButtonsStock->builder = mainDashBoard;
    mainDashButtonsStock->Node = mainNodes;

    listProduitsGetSelected(listProd,mainDashButtons);
    listProduitsGetSelectedStock(gesstock,mainDashButtonsStock);

    snprintf(sumOfProdChar, sizeof(sumOfProdChar), "%d", sumOfProducts);
    gchar *concatenated_str = g_malloc(strlen(customLabel) + strlen(sumOfProdChar) + 1); // +1 for null terminator

    strcpy(concatenated_str, customLabel);
    strcat(concatenated_str, sumOfProdChar);
    gtk_label_set_text(total_pro,(const gchar *)concatenated_str);

    rechDataTab * newrechdata = g_new(rechDataTab,2);
    newrechdata->rech1 = recherchedata;
    newrechdata->rech2 = recherchedata2;


    g_signal_connect(ajout_prod,"clicked",G_CALLBACK(addProduitNouveau), newrechdata);
    g_signal_connect(montant,"changed",G_CALLBACK(handleMontant),mainDashButtons);
    g_signal_connect(proc_caisse,"clicked",G_CALLBACK(handleCaissePress), mainDashButtons);


    gtk_widget_set_sensitive(suppr_element_caisse,FALSE);



    gtk_widget_set_name(GTK_WIDGET(window), "windowDash");
    gtk_widget_set_name(GTK_WIDGET(containerItems),"containerItemsDash");
    gtk_widget_set_name(GTK_WIDGET(listProd),"listProduct");
    gtk_widget_set_name(GTK_WIDGET(content_ut_tree),"ut_table_tree");
    gtk_widget_set_name(GTK_WIDGET(ajout_caisse), "buttonsDash");
    gtk_widget_set_name(GTK_WIDGET(ajout_prod), "buttonsDash");
    gtk_widget_set_name(GTK_WIDGET(checkout), "buttonsDash");
    gtk_widget_set_name(GTK_WIDGET(suppr_prod), "buttonsDash");
    gtk_widget_set_name(GTK_WIDGET(supprtouscaisse), "buttonsDash");
    gtk_widget_set_name(GTK_WIDGET(suppr_element_caisse), "buttonsDash");
    gtk_widget_set_name(GTK_WIDGET(hbuttonCaisse), "hbCaisse");
    gtk_widget_set_name(GTK_WIDGET(mainGrid), "windowDash");
    gtk_widget_set_name(GTK_WIDGET(recherche_entry), "inputes");
    gtk_widget_set_name(GTK_WIDGET(recherche2), "inputes");
    gtk_widget_set_name(GTK_WIDGET(containerCaisse), "windowDash");
    gtk_widget_set_name(GTK_WIDGET(ajout_utilisateur),"buttonsDash");
    //gtk_widget_set_name(GTK_WIDGET(containerProd), "containerProd");
    gtk_widget_set_name(GTK_WIDGET(recherche_box), "recherche_box");
    gtk_widget_set_name(GTK_WIDGET(vendeur), "recherche_box");
    gtk_widget_set_name(GTK_WIDGET(containerProdSTOCK), "containerProdStock");
    gtk_widget_set_name(GTK_WIDGET(containerItemsStock), "containerProdItems");
     gtk_widget_set_name(GTK_WIDGET(tree_rec_container), "rec_tree_container");
    gtk_widget_set_name(GTK_WIDGET(containerWidget), "containerWidg");
    gtk_widget_set_name(GTK_WIDGET(containergessstock), "containergessstock");
     gtk_widget_set_name(GTK_WIDGET(proc_caisse), "buttonsDash");
    gtk_widget_set_name(GTK_WIDGET(bt1), "numsInput");
    gtk_widget_set_name(GTK_WIDGET(bt2), "numsInput");
    gtk_widget_set_name(GTK_WIDGET(bt3), "numsInput");
    gtk_widget_set_name(GTK_WIDGET(bt4), "numsInput");
    gtk_widget_set_name(GTK_WIDGET(bt5), "numsInput");
    gtk_widget_set_name(GTK_WIDGET(bt6), "numsInput");
    gtk_widget_set_name(GTK_WIDGET(bt7), "numsInput");
    gtk_widget_set_name(GTK_WIDGET(bt8), "numsInput");
    gtk_widget_set_name(GTK_WIDGET(bt9), "numsInput");
    gtk_widget_set_name(GTK_WIDGET(bt0), "numsInput");
    gtk_widget_set_name(GTK_WIDGET(numpadBox), "numpad");
    gtk_widget_set_name(GTK_WIDGET(textContainerCaisse), "textContainerCaisse");
     gtk_widget_set_name(GTK_WIDGET(caisse_tree_scroll), "treeScrollCaisse");
     gtk_widget_set_name(GTK_WIDGET(add_ut_scroll), "addUserScroll");
     gtk_widget_set_name(GTK_WIDGET(tree_rec_container), "containerProd");
     gtk_widget_set_name(GTK_WIDGET(vendeur_input), "containerProd");

    load_css(window,"styles.css","windowDash");
    //load_css(containerItems,"styles.css","containerItemsDash");
    load_css(listProd, "styles.css", "listProduct");
    load_css(ajout_caisse, "styles.css",  "buttonsDash");
    load_css(ajout_prod, "styles.css",  "buttonsDash");
    load_css(ajout_utilisateur, "styles.css",  "buttonsDash");
    load_css(bt1, "styles.css", "numsInput");
    load_css(bt2, "styles.css", "numsInput");
    load_css(bt3, "styles.css", "numsInput");
    load_css(bt4, "styles.css", "numsInput");
    load_css(bt5, "styles.css", "numsInput");
    load_css(bt6, "styles.css", "numsInput");
    load_css(bt7, "styles.css", "numsInput");
    load_css(bt8, "styles.css", "numsInput");
    load_css(bt9, "styles.css", "numsInput");
    load_css(bt0, "styles.css", "numsInput");
    load_css(containerCaisse,"styles.css","windowDash");
        load_css(content_ut_tree,"styles.css","ut_table_tree");
    load_css(numpadBox, "styles.css", "numpad");
    load_css(textContainerCaisse,"styles.css","textContainerCaisse");
    load_css(caisse_tree_scroll,"styles.css","treeScrollCaisse");
    load_css(container_rec,"styles.css","container_rec");
    load_css(hbuttonCaisse,"styles.css","hbCaisse");
     load_css(add_ut_scroll,"styles.css","addUserScroll");
    load_css(ajout_utilisateur, "styles.css",  "buttonsDash");
    load_css(checkout, "styles.css",  "buttonsDash");
    load_css(suppr_prod, "styles.css",  "buttonsDash");
     load_css(supprtouscaisse, "styles.css",  "buttonsDash");
      load_css(proc_caisse, "styles.css",  "buttonsDash");
      load_css(suppr_element_caisse, "styles.css",  "buttonsDash");
    load_css(mainGrid, "styles.css", "windowDash");
    // load_css(containerProd, "styles.css", "containerProd");
    load_css(recherche_box, "styles.css", "recherche_box");
    load_css(vendeur, "styles.css", "recherche_box");
    load_css(containerProdSTOCK, "styles.css", "containerProdStock");
    load_css(containergessstock, "styles.css", "containergessstock");
    load_css(tree_rec_container, "styles.css", "containerProd");
     load_css(vendeur_input, "styles.css", "containerProd");
    load_css(recherche2, "styles.css", "inputes");
    load_css(recherche_entry, "styles.css", "inputes");
    // load_css(containerItemsStock, "styles.css", "containerProdItems");
    load_css(containerWidget,"styles.css", "containerWidg");



    gtk_widget_show_all(GTK_WIDGET(window));


    gtk_main();
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);
    g_object_unref(mainDashBoard);



}






int main(int argc, char *argv[])
{
    GtkBuilder *builder;
    GtkWindow *window;
    GtkButton * loginBtn;





    gtk_init(&argc, &argv);


    builder = gtk_builder_new();

    GError *error = NULL;
    if (!gtk_builder_add_from_resource(builder, "/com/gec/saifeddine/login.glade", &error))
    {
        g_error("Failed to load UI file: %s", error->message);
        g_clear_error(&error);
        return 1;
    }



    window = GTK_WINDOW(gtk_builder_get_object(builder, "gec"));
    loginBtn = GTK_BUTTON(gtk_builder_get_object(builder, "login"));
    GtkVButtonBox * containerLogin = GTK_WIDGET(gtk_builder_get_object(builder, "containerfi"));
    GtkEntry *USER = GTK_ENTRY(gtk_builder_get_object(builder, "user"));
    GtkEntry *PASS = GTK_ENTRY(gtk_builder_get_object(builder, "pass"));

    gtk_widget_set_name(USER,"user");
    gtk_widget_set_name(PASS,"pass");
    gtk_widget_set_name(containerLogin,"containerLogin");
    gtk_widget_set_name(window,"windowLogin");



    CallbackData  *data = g_new(CallbackData, 1);
    data->builder = builder;
    g_signal_connect(loginBtn, "clicked", G_CALLBACK(check_login), data);


    gtk_builder_connect_signals(builder, NULL);


    load_css(GTK_WIDGET(loginBtn), "styles.css","login");
    load_css(USER,"styles.css","user");
    load_css(PASS,"styles.css","pass");
    load_css(containerLogin,"styles.css","containerLogin");
    load_css(window,"styles.css","windowLogin");


    gtk_widget_show_all(GTK_WIDGET(window));


    gtk_main();
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);
    gtk_widget_destroy(window);
    g_object_unref(builder);

    return 0;
}
void populateTableAgain(productNode mainNode, rechercheData * recherchedata)
{
    GtkTreeView *listProd;
    GtkListStore *newListStore;


    listProd = recherchedata->treeview;
    newListStore = recherchedata->newListStore;

    gtk_list_store_clear(newListStore);


    while (mainNode->next != NULL)
    {
        addProducts(listProd, newListStore, mainNode->next->product.productName, mainNode->next->product.productDescription, mainNode->next->product.productPrice, mainNode->next->product.productQuantity, mainNode->next->product.productRef);
        mainNode = mainNode->next;
    }
}

void populateTableAgainRec(ReceiptNodes mainNode, rechercheData * recherchedata) {
    GtkTreeView *recTreeView;
    GtkListStore *newListStore;
    ReceiptNodes current = mainNode;
    recTreeView = recherchedata->treeview;
    newListStore = recherchedata->newListStore;

    gtk_list_store_clear(newListStore);

    while (current != NULL) {
        addProductsRec(recTreeView, newListStore, current->receipt, "0");
        current = current->next;
    }
}


void populateTableAgainUser(usersNode mainNode, rechercheData * recherchedata) {
    GtkTreeView *recTreeView;
    GtkListStore *newListStore;
    usersNode current = mainNode;
    recTreeView = recherchedata->treeview;
    newListStore = recherchedata->newListStore;

    gtk_list_store_clear(newListStore);

    while (current != NULL) {
        addUsers(recTreeView,recherchedata->newListStore, current->user.UserName,"########",current->user.Role);
        current = current->next;
    }
}


void recherche_produits(GtkEditable *widget, gpointer data)
{
    GtkEntry *entry = GTK_ENTRY(widget);
    rechercheData *recherchedata = (rechercheData *)data;
    GtkTreeView *listProd = recherchedata->treeview;
    gchar *text = gtk_entry_get_text(entry);

    if (strcmp(text, "") == 0)
    {
        gtk_list_store_clear(recherchedata->newListStore);
        populateTableAgain(recherchedata->mainNode,recherchedata);
        return;
    }

    productNode currentNode = recherchedata->mainNode;
    gboolean found = FALSE;

    while (currentNode != NULL)
    {

        if (strstr(currentNode->product.productName, text) != NULL ||
                strstr(currentNode->product.productDescription, text) != NULL ||
                strstr(g_strdup_printf("%.2f", currentNode->product.productPrice), text) != NULL ||
                strstr(g_strdup_printf("%d", currentNode->product.productQuantity), text) != NULL ||
                strstr(currentNode->product.productRef, text) != NULL)
        {


            found = TRUE;

            gtk_list_store_clear(recherchedata->newListStore);
            addProducts(listProd, recherchedata->newListStore,
                        currentNode->product.productName,
                        currentNode->product.productDescription,
                        currentNode->product.productPrice,
                        currentNode->product.productQuantity,
                        currentNode->product.productRef);
        }
        currentNode = currentNode->next;
    }

    if (!found)
    {
        gtk_list_store_clear(recherchedata->newListStore);
    }
}

void recherche_utd(GtkEditable *widget, gpointer data) {
    GtkEntry *entry = GTK_ENTRY(widget);
    rechercheData *recherchedata = (rechercheData *)data;
    GtkTreeView *recTreeView = recherchedata->treeview;
    gchar *text = gtk_entry_get_text(entry);

    gtk_list_store_clear(recherchedata->newListStore);

    if (g_strcmp0(text, "") == 0) {
        start_timer(globElem);
        populateTableAgainUser(recherchedata->users, recherchedata);
        return;
    }

    usersNode currentNode = recherchedata->users;
    gboolean found = FALSE;

    while (currentNode != NULL) {
        if (strstr(currentNode->user.UserName, text) != NULL || strstr(currentNode->user.Role, text) != NULL) {
                stop_timer();
            found = TRUE;
            addUsers(recTreeView,recherchedata->newListStore, currentNode->user.UserName,"########",currentNode->user.Role);
        }
        currentNode = currentNode->next;
    }

    if (!found) {
            stop_timer();
        gtk_list_store_clear(recherchedata->newListStore);
    }
}

void recherche_vendeur(GtkEditable *widget, gpointer data) {
    GtkEntry *entry = GTK_ENTRY(widget);
    rechercheData *recherchedata = (rechercheData *)data;
    GtkTreeView *recTreeView = recherchedata->treeview;
    gchar *text = gtk_entry_get_text(entry);

    gtk_list_store_clear(recherchedata->newListStore);

    if (g_strcmp0(text, "") == 0) {
        populateTableAgainRec(recherchedata->receiptNode, recherchedata);
        return;
    }

    ReceiptNodes currentNode = recherchedata->receiptNode;
    gboolean found = FALSE;

    while (currentNode != NULL) {
        if (strstr(currentNode->receipt, text) != NULL) {
            found = TRUE;
            addProductsRec(recTreeView, recherchedata->newListStore, currentNode->receipt, "0");
        }
        currentNode = currentNode->next;
    }

    if (!found) {
        gtk_list_store_clear(recherchedata->newListStore);
    }
}





gboolean remove_selections(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    GtkTreeSelection * selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(widget));
    gtk_tree_selection_unselect_all(selection);
    return FALSE;
}

void addProducts(GtkTreeView *treeProds, GtkListStore *listStore, gchar *productName, gchar *productDescription, gchar *productPrice, gchar *productQuantity, gchar *productRef)
{
    GtkTreeIter iter;
    gtk_list_store_append(listStore, &iter);
    gtk_list_store_set(listStore, &iter, 0, productName, 1, productDescription, 2, productPrice, 3, productQuantity, 4, productRef, -1);
}

void addProductsRec(GtkTreeView *treeProds, GtkListStore *listStore, gchar *Recette, gchar * Id)
{
    GtkTreeIter iter;
    gtk_list_store_append(listStore, &iter);
    gtk_list_store_set(listStore, &iter, 0, Recette, 1, Id, -1);
}

void addUsers(GtkTreeView *treeProds, GtkListStore *listStore, gchar *Username, gchar * Password, gchar * Role)
{
    GtkTreeIter iter;
    gtk_list_store_append(listStore, &iter);
    gtk_list_store_set(listStore, &iter, 0, Username, 1, Password,2,Role, -1);
}

void addProdCaisse(GtkTreeView *treeProds, GtkListStore *listStore, gchar *productName, gchar *productDescription, gchar *productPrice, gchar *productQuantity)
{
    GtkTreeIter iter;
    gtk_list_store_append(listStore, &iter);
    gtk_list_store_set(listStore, &iter, 0, productName, 1, productDescription, 2, productPrice, 3, productQuantity, -1);
}




void check_login(GtkWidget *widget, gpointer data)
{
    CallbackData *newData = (CallbackData *)data;
    GtkBuilder *newBuilder = newData->builder;
    GError *error = NULL;
    GtkDialog * errorDiag;

    GtkWindow * loginWindow;

    GtkBuilder * dashBuilder = gtk_builder_new();
    GtkWidget* noteBook;

    if(!gtk_builder_add_from_resource(dashBuilder,"/com/gec/saifeddine/main.glade",NULL))
    {
        printf("Failed to init dash builder:");
    }

    GtkEntry *USER = GTK_ENTRY(gtk_builder_get_object(newBuilder, "user"));
    GtkEntry *PASS = GTK_ENTRY(gtk_builder_get_object(newBuilder, "pass"));

    noteBook = GTK_NOTEBOOK(gtk_builder_get_object(dashBuilder,"noteMain"));

    userG = gtk_entry_get_text(USER);
    passG = gtk_entry_get_text(PASS);

    const gchar *userText = gtk_entry_get_text(USER);
    const gchar *passText = gtk_entry_get_text(PASS);
    User user;
    strcpy(user.UserName,"");
    strcpy(user.Password,"");
    strcpy(user.Role,"");
    usersNode Head = NULL;  // Initialize the head node to NULL

    loginWindow = GTK_WINDOW(gtk_builder_get_object(newBuilder, "gec"));
    if (loginWindow == NULL)
    {
        g_error("Login not initalized");
        return;
    }

    if(strcmp("",userText)==0 || strcmp("",passText)==0)
    {
        GtkDialog * errorDiag = gtk_message_dialog_new(loginWindow,GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Password or username shouldn't be empty");
        gtk_window_set_title(GTK_WINDOW(errorDiag),"Error");
        gtk_dialog_run(GTK_DIALOG(errorDiag));
        gtk_widget_destroy(errorDiag);
    }

    int result = readFromFileUsers("users.txt",userText,passText,&Head);
    if (result == 1)
    {
        gtk_widget_hide(loginWindow);
        Dashboard(dashBuilder, Head);
    } else if (result == 2)
    {
        disable_notebook_tab(noteBook,1);
        disable_notebook_tab(noteBook,3);
        disable_notebook_tab(noteBook,4);
        gtk_widget_hide(loginWindow);

        Dashboard(dashBuilder, Head);

    }
    else
    {
        errorDiag = gtk_message_dialog_new(loginWindow,GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Password or username is incorrect");
        gtk_window_set_title(GTK_WINDOW(errorDiag),"Error");
        gtk_dialog_run(GTK_DIALOG(errorDiag));
        gtk_widget_destroy(errorDiag);
    }
}






void addColumns(gchar *title, GtkTreeView *treeView, gint index)
{
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes(title, renderer, "text",index, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeView), column);
}


productNode createProduct(Product product)
{
    productNode new_Product_Node;
    new_Product_Node = (productNode)malloc(sizeof(mainNode));

    new_Product_Node->product = product;
    new_Product_Node->next = NULL;

    return new_Product_Node;
}


void handleQuantity(GtkEditable *editable, gpointer data)
{
    GtkEntry *entry = GTK_ENTRY(editable);

    const gchar *text = gtk_entry_get_text(entry);




    if(_strtoi64(text,NULL,10) <= 0)
    {

        gtk_entry_set_text(entry,"");
    }
    else
    {

    }


}

void handleAccept(GtkWidget * widget,  gpointer user_data)
{
    getData * selecData = (getData *) user_data;
    GtkTreeView * caisse_container;
    GtkButton * proc_caisse;
    GtkLabel * getTotalLabel;
    GtkWidget * NoteBookMain;

    gchar * text = gtk_entry_get_text(selecData->text);
    GtkBuilder * builder = gtk_builder_new();


    if(!gtk_builder_add_from_resource(builder,"/com/gec/saifeddine/main.glade",NULL))
    {
        g_print("Failed to initialize");
    }

    caisse_container = GTK_TREE_VIEW(gtk_builder_get_object(selecData->builder,"les_items_caisse"));
    proc_caisse = GTK_BUTTON(gtk_builder_get_object(selecData->builder,"proc_caisse"));
    getTotalLabel =GTK_LABEL(gtk_builder_get_object(selecData->builder,"total_sum"));
    NoteBookMain = GTK_WIDGET(gtk_builder_get_object(selecData->builder,"noteMain"));


     if (g_strcmp0(text, "") == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "\nLa quantite ne doit pas etre vide");

        gtk_window_set_title(GTK_WINDOW(dialog), "Erreur");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    if(_strtoi64(text,NULL,10) > _strtoi64(selecData->q,NULL,10))
    {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                            GTK_DIALOG_MODAL,
                            GTK_MESSAGE_ERROR,
                            GTK_BUTTONS_OK,
                            "\nLa quantite entree doit etre inferieur ou egale \nla quantite initiale");


        gtk_window_set_title(GTK_WINDOW(dialog), "Erreur");


        gtk_dialog_run(GTK_DIALOG(dialog));


        gtk_widget_destroy(dialog);
        return;
    }

   gfloat prixTot = strtof(selecData->p,NULL) * strtof(text,NULL);
  const gchar *labelTotalText = gtk_label_get_text(getTotalLabel);
    gfloat getLabelInt = strtof(labelTotalText, NULL) + prixTot;

    gchar sumChar[70];
    sprintf(sumChar, "%.2f", getLabelInt);
    gtk_label_set_text(getTotalLabel, sumChar);


   gchar prixTotChar[50];
   sprintf(prixTotChar, "%.2f", prixTot);



    addProdCaisse(caisse_container,CAISSE_LISTSTORE,text,selecData->n,selecData->p,prixTotChar);
    gtk_tree_view_set_model(caisse_container, GTK_TREE_MODEL(CAISSE_LISTSTORE));


     int  itemsCount = getItemsCount(caisse_container);
    if (itemsCount != 0) {
        enable_notebook_tab(GTK_NOTEBOOK(NoteBookMain),2);
    }
     gtk_widget_destroy(quantity_dialog);
    quantity_dialog = NULL;


}

void ajoutDansLaCaisse(GtkWidget * widget, gpointer data)
{
    getData * selecData = (getData*)data;
    GtkBuilder * builder = gtk_builder_new();
    GtkEntry * quantity;
    GtkButton * acceptButton;
    GtkLabel * labelQuan;
    GtkLabel * labelP;

    if(!gtk_builder_add_from_resource(builder, "/com/gec/saifeddine/quantity.glade", NULL))
    {
        printf("Quantity not initalized");
    }

    if (quantity_dialog != NULL) {
        gtk_widget_destroy(quantity_dialog);
        quantity_dialog = NULL;
    }


    quantity_dialog = GTK_WIDGET(gtk_builder_get_object(builder, "quantityd"));
    quantity = GTK_ENTRY(gtk_builder_get_object(builder,"quan"));
    acceptButton = GTK_WIDGET(gtk_builder_get_object(builder, "accept"));
    labelQuan = GTK_WIDGET(gtk_builder_get_object(builder,"totale_quan"));
    labelP = GTK_WIDGET(gtk_builder_get_object(builder,"prodlab"));



    selecData->text = quantity;

    gchar result[80];
    gchar result2[80];

    sprintf(result, "Quantite Initiale: %s\n",selecData->q );
    sprintf(result2, "Produit: %s",selecData->n );

    gtk_label_set_text(labelQuan,result);
   gtk_label_set_text(labelP,result2);
   gtk_widget_set_name(GTK_WIDGET(acceptButton),"buttonsDash");
    load_css(acceptButton,"styles.css","buttonsDash");
    gtk_widget_set_name(GTK_WIDGET(quantity),"inputes");
    load_css(quantity,"styles.css","inputes");

    g_signal_connect(acceptButton,"clicked",G_CALLBACK(handleAccept), selecData);





    g_signal_connect(quantity,"changed",G_CALLBACK(handleQuantity),  NULL);




   gtk_window_set_transient_for(GTK_WINDOW(quantity_dialog), GTK_WINDOW(gtk_widget_get_toplevel(widget)));
    gtk_window_set_modal(GTK_WINDOW(quantity_dialog), TRUE);

    gtk_widget_show_all(quantity_dialog);


}



