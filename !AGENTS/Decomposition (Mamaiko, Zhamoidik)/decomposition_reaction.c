
#include "decomposition_reaction.h"
#include "search_keynodes.h"
#include "search_utils.h"
#include "search.h"
#include "utils.h"
#include "stdio.h"


//#include "sc-memory/cpp/sc_struct.hpp"


sc_result agent_decomposition_reaction(const sc_event *event, sc_addr arg)
{  sc_addr question, answer;
    sc_iterator3 *it1, *it2;
    sc_bool sys_off = SC_TRUE;
    sc_addr substance;
    sc_addr nrel_inclusion;
    sc_addr nrel_count_of_inclusion;
    sc_addr number;
    sc_addr nrel_decomposition;
    sc_addr set_of_elements;
    sc_addr concept_binary_elements;
    sc_addr concept_nonmetals;
    set_of_elements=sc_memory_node_new(s_default_ctx, sc_type_const);//создал множество хим элементов данного вещества

    if (!sc_memory_get_arc_end(s_default_ctx, arg, &question))
        return SC_RESULT_ERROR_INVALID_PARAMS;


    if (sc_helper_check_arc(s_default_ctx, keynode_question_decomposition_reaction, question, sc_type_arc_pos_const_perm) == SC_FALSE)
        return SC_RESULT_ERROR_INVALID_TYPE;

 answer = create_answer_node();
 sc_helper_resolve_system_identifier(s_default_ctx, "concept_nonmetals", &concept_nonmetals);
 sc_helper_resolve_system_identifier(s_default_ctx, "concept_binary_elements", &concept_binary_elements);
 sc_helper_resolve_system_identifier(s_default_ctx, "nrel_decomposition", &nrel_decomposition);
 sc_helper_resolve_system_identifier(s_default_ctx, "nrel_inclusion", &nrel_inclusion);
 sc_helper_resolve_system_identifier(s_default_ctx, "nrel_count_of_inclusion", &nrel_count_of_inclusion);
 sc_helper_resolve_system_identifier(s_default_ctx, "number", &number);
/* sc_addr PI=sc_memory_node_new(s_default_ctx,sc_type_const);
 sc_addr P=sc_memory_node_new(s_default_ctx,sc_type_const);
 sc_memory_arc_new(s_default_ctx,sc_type_const, PI,P);

sc_iterator3 *iterator = sc_iterator3_f_a_a_new(s_default_ctx,
                                                PI,
                                               sc_type_const,
                                               0

                                                    );
if(sc_iterator3_next(iterator))
   { appendIntoAnswer(answer, sc_iterator3_value(iterator,2));
appendIntoAnswer(answer, sc_iterator3_value(iterator,0));
appendIntoAnswer(answer, sc_iterator3_value(iterator,1));
}
*/
 printf("Agent initiated!\n");
// printEl(s_default_ctx, arg);
// check question type

 /* нахожу дугу от задаваемого вопроса с исходным веществом substance и добавляю в ответ*/
 it1 = sc_iterator3_f_a_a_new(s_default_ctx,
                              question,
                              sc_type_arc_pos_const_perm,
                              0);
 if (sc_iterator3_next(it1) == SC_TRUE)
 {
     substance = sc_iterator3_value(it1, 2);
   //  appendIntoAnswer(answer, sc_iterator3_value(it1, 2));
 }
 sc_iterator3_free(it1);//очищаю итератор

 /* исследую дуги исходящие от substance и добавляю в ответ*/
 sc_iterator5 *iter5;
 sc_iterator5 *iter5_2;
int kolich=0;
 iter5 = sc_iterator5_f_a_a_a_f_new(s_default_ctx,
                              substance,
                              sc_type_arc_common | sc_type_const,
                              0,
                              sc_type_arc_pos_const_perm,
                              nrel_inclusion );
while (sc_iterator5_next(iter5) == SC_TRUE)
 {kolich++;

    sc_addr element = sc_iterator5_value(iter5, 2);
    sc_memory_arc_new(s_default_ctx,sc_type_arc_pos_const_perm, set_of_elements,sc_iterator5_value(iter5, 2) );//добавляю хим эл во множество
  //  appendIntoAnswer(answer, sc_iterator5_value(iter5, 4));
  //  appendIntoAnswer(answer, sc_iterator5_value(iter5, 3));
  //  appendIntoAnswer(answer, sc_iterator5_value(iter5, 2));
  //  appendIntoAnswer(answer, sc_iterator5_value(iter5, 1));
  //  appendIntoAnswer(answer, sc_iterator5_value(iter5, 0));
    ///////////////////////////////
 /*   iter5_2 = sc_iterator5_f_a_a_a_f_new(s_default_ctx,
                                 substance,
                                 sc_type_arc_common | sc_type_const,
                                 0,
                                 sc_type_arc_pos_const_perm,
                                 nrel_count_of_inclusion );
   while (sc_iterator5_next(iter5_2) == SC_TRUE)
    {
       sc_addr count_of_inclusion = sc_iterator5_value(iter5_2, 2);

       appendIntoAnswer(answer, sc_iterator5_value(iter5_2, 4));
       appendIntoAnswer(answer, sc_iterator5_value(iter5_2, 3));
       appendIntoAnswer(answer, sc_iterator5_value(iter5_2, 2));
       appendIntoAnswer(answer, sc_iterator5_value(iter5_2, 1));
       appendIntoAnswer(answer, sc_iterator5_value(iter5_2, 0));
       ///////////////////////////////
       it1 = sc_iterator3_f_a_f_new(s_default_ctx,
                                    count_of_inclusion,
                                    sc_type_arc_pos_const_perm,
                                    number);
       if (sc_iterator3_next(it1) == SC_TRUE)
       {
           appendIntoAnswer(answer, sc_iterator3_value(it1, 2));
           appendIntoAnswer(answer, sc_iterator3_value(it1, 1));
           appendIntoAnswer(answer, sc_iterator3_value(it1, 0));
       }
       sc_iterator3_free(it1);//очищаю итератор
       ////////////////////////////////
    }
   sc_iterator5_free(iter5_2);*/
    ////////////////////////////////
 }
sc_iterator5_free(iter5);

sc_addr node;
node = sc_memory_node_new(s_default_ctx,sc_type_const);
sc_addr arc1= sc_memory_arc_new(s_default_ctx,sc_type_arc_common | sc_type_const,node, substance);
sc_addr arc2 = sc_memory_arc_new(s_default_ctx,sc_type_arc_pos_const_perm, nrel_decomposition, arc1);


/*sc_addr system_idtf;
sc_helper_resolve_system_identifier(s_default_ctx, "nrel_system_identifier", &system_idtf);
sc_addr link = sc_memory_node_new(s_default_ctx, sc_type_const);
link = genStringNode(s_default_ctx, "2");
sc_addr arc= sc_memory_arc_new(s_default_ctx, sc_type_arc_common | sc_type_const, node, link);
sc_memory_arc_new(s_default_ctx, sc_type_arc_pos_const_perm, system_idtf, arc);
*/

appendIntoAnswer(answer, node);
appendIntoAnswer(answer, arc1);
appendIntoAnswer(answer, substance);
appendIntoAnswer(answer, nrel_decomposition);
appendIntoAnswer(answer, arc2);

SC_ADDR_MAKE_EMPTY(arc1);
SC_ADDR_MAKE_EMPTY(arc2);

if(kolich==2)//если в веществе 2 вида атомов
{
it2 = sc_iterator3_f_a_a_new(s_default_ctx,
                             set_of_elements,
                             sc_type_arc_pos_const_perm,
                             0);
while( sc_iterator3_next(it2)==SC_TRUE)
{ sc_addr empty_node=sc_memory_node_new(s_default_ctx, sc_type_const);
    sc_addr him_element;

    him_element=sc_iterator3_value(it2, 2);

    int k=1;
    sc_iterator3 *iterator;
    iterator = sc_iterator3_f_a_f_new(s_default_ctx,
                                  concept_binary_elements,
                                  sc_type_arc_pos_const_perm,
                                  him_element

                                    );

if(sc_iterator3_next(iterator))
    k=2;
   sc_iterator3_free(iterator);

    arc1=sc_memory_arc_new(s_default_ctx, sc_type_arc_pos_const_perm, node, empty_node);
    appendIntoAnswer(answer, empty_node);
    appendIntoAnswer(answer, arc1);

SC_ADDR_MAKE_EMPTY(arc1);


sc_addr arc1= sc_memory_arc_new(s_default_ctx,sc_type_arc_common | sc_type_const,empty_node, him_element);
sc_addr arc2 = sc_memory_arc_new(s_default_ctx,sc_type_arc_pos_const_perm, nrel_inclusion, arc1);
appendIntoAnswer(answer, him_element);
appendIntoAnswer(answer, arc1);
appendIntoAnswer(answer, arc2);
appendIntoAnswer(answer, nrel_inclusion);
SC_ADDR_MAKE_EMPTY(arc1);
SC_ADDR_MAKE_EMPTY(arc2);

sc_addr link = sc_memory_node_new(s_default_ctx, sc_type_const);
link = genIntNode(s_default_ctx, k);
arc1= sc_memory_arc_new(s_default_ctx,sc_type_arc_common | sc_type_const,him_element, link);
arc2 = sc_memory_arc_new(s_default_ctx,sc_type_arc_pos_const_perm, nrel_count_of_inclusion, arc1);
appendIntoAnswer(answer, nrel_count_of_inclusion);
appendIntoAnswer(answer, arc1);
appendIntoAnswer(answer, arc2);
appendIntoAnswer(answer, link);
SC_ADDR_MAKE_EMPTY(empty_node);
SC_ADDR_MAKE_EMPTY(arc1);
SC_ADDR_MAKE_EMPTY(arc2);
SC_ADDR_MAKE_EMPTY(link);
}

}

if(kolich==3)
{

    sc_addr concept_acid;
    sc_helper_resolve_system_identifier(s_default_ctx, "concept_acid", &concept_acid);
sc_addr oxygen;
sc_helper_resolve_system_identifier(s_default_ctx,"O",&oxygen);

    sc_iterator3 *acids;///////------/-/-/-/-/-/-/-/-/-/-/-/--/-/-/-/-/-/--//-
    acids= sc_iterator3_f_a_f_new(s_default_ctx,
                                  concept_acid,
                                  sc_type_arc_pos_const_perm,
                                  substance
                                  );
    if(sc_iterator3_next(acids))//если нашло в кислотах
    {   sc_addr concept_acidic_oxide;
        sc_helper_resolve_system_identifier(s_default_ctx,"concept_acidic_oxide",&concept_acidic_oxide);
        sc_iterator3 *nonmetals;
        nonmetals= sc_iterator3_f_a_a_new(s_default_ctx,
                                         set_of_elements,
                                         sc_type_arc_pos_const_perm,
                                         0);
        sc_addr nonmet;
        while(sc_iterator3_next(nonmetals)==SC_TRUE)
        {
            nonmet=sc_iterator3_value(nonmetals,2);
            if(SC_ADDR_IS_EQUAL(oxygen,nonmet))
            continue;
                sc_iterator3 *acid_oxyde;
        acid_oxyde= sc_iterator3_f_a_a_new(s_default_ctx,
                                           concept_acidic_oxide,
                                           sc_type_arc_pos_const_perm,
                                           0);
        while(sc_iterator3_next(acid_oxyde))
        {
        sc_addr acid=sc_iterator3_value(acid_oxyde,2);

        sc_iterator3 *acid_oxyde;
        acid_oxyde= sc_iterator3_f_a_a_new(s_default_ctx,
                                           acid,
                                           sc_type_arc_pos_const_perm,
                                           0);
        while(sc_iterator3_next(acid_oxyde))
        {
            if(SC_ADDR_IS_EQUAL(nonmet,sc_iterator3_value(acid_oxyde,2)))
            {
                sc_addr arc3_1= sc_memory_arc_new(s_default_ctx,sc_type_arc_pos_const_perm,node, acid);

                appendIntoAnswer(answer,acid);
                appendIntoAnswer(answer,arc3_1);
                SC_ADDR_MAKE_EMPTY(arc3_1);
            }

        }

sc_iterator3_free(acid_oxyde);
        }

        }
sc_addr h2o;
h2o=sc_memory_node_new(s_default_ctx,sc_type_const);
        sc_addr system_idtf;
        sc_helper_resolve_system_identifier(s_default_ctx, "nrel_system_identifier", &system_idtf);
        sc_addr link = sc_memory_node_new(s_default_ctx, sc_type_const);
        link = genStringNode(s_default_ctx, "H2O");
        sc_addr arc= sc_memory_arc_new(s_default_ctx, sc_type_arc_common | sc_type_const, h2o, link);
        sc_memory_arc_new(s_default_ctx, sc_type_arc_pos_const_perm, system_idtf, arc);

        sc_addr arc3_1= sc_memory_arc_new(s_default_ctx,sc_type_arc_pos_const_perm,node, h2o);

        appendIntoAnswer(answer,h2o);
        appendIntoAnswer(answer,arc3_1);
        SC_ADDR_MAKE_EMPTY(arc3_1);

    }
    else{
    sc_iterator3_free(acids);//////////////////////////////////////////////////////////////////////////////////////////

    sc_addr concept_bases;
    sc_helper_resolve_system_identifier(s_default_ctx, "concept_bases", &concept_bases);

    sc_iterator3 *basics;
    basics= sc_iterator3_f_a_f_new(s_default_ctx,
                                  concept_bases,
                                  sc_type_arc_pos_const_perm,
                                  substance
                                  );
    if(sc_iterator3_next(basics))//если нашло в основаниях
    {   sc_addr concept_basic_oxide; printf("3\n");
        sc_helper_resolve_system_identifier(s_default_ctx,"concept_basic_oxide",&concept_basic_oxide);
        sc_iterator3 *nonmetals;
        nonmetals= sc_iterator3_f_a_a_new(s_default_ctx,
                                         set_of_elements,
                                         sc_type_arc_pos_const_perm,
                                         0);
        sc_addr nonmet;
        while(sc_iterator3_next(nonmetals)==SC_TRUE)
        {
            nonmet=sc_iterator3_value(nonmetals,2);
            if(SC_ADDR_IS_EQUAL(oxygen,nonmet))
            continue;
                sc_iterator3 *basic_oxyde;
        basic_oxyde= sc_iterator3_f_a_a_new(s_default_ctx,
                                           concept_basic_oxide,
                                           sc_type_arc_pos_const_perm,
                                           0);
        while(sc_iterator3_next(basic_oxyde))
        {
        sc_addr basic=sc_iterator3_value(basic_oxyde,2);

        sc_iterator3 *basic_oxyde;
        basic_oxyde= sc_iterator3_f_a_a_new(s_default_ctx,
                                           basic,
                                           sc_type_arc_pos_const_perm,
                                           0);
        while(sc_iterator3_next(basic_oxyde))
        {
            if(SC_ADDR_IS_EQUAL(nonmet,sc_iterator3_value(basic_oxyde,2)))
            {
                sc_addr arc3_1= sc_memory_arc_new(s_default_ctx,sc_type_arc_pos_const_perm,node, basic);

                appendIntoAnswer(answer,basic);
                appendIntoAnswer(answer,arc3_1);
                SC_ADDR_MAKE_EMPTY(arc3_1);
            }

        }

sc_iterator3_free(basic_oxyde);
        }

        }
sc_addr h2o;
h2o=sc_memory_node_new(s_default_ctx,sc_type_const);
        sc_addr system_idtf;
        sc_helper_resolve_system_identifier(s_default_ctx, "nrel_system_identifier", &system_idtf);
        sc_addr link = sc_memory_node_new(s_default_ctx, sc_type_const);
        link = genStringNode(s_default_ctx, "H2O");
        sc_addr arc= sc_memory_arc_new(s_default_ctx, sc_type_arc_common | sc_type_const, h2o, link);
        sc_memory_arc_new(s_default_ctx, sc_type_arc_pos_const_perm, system_idtf, arc);

        sc_addr arc3_1= sc_memory_arc_new(s_default_ctx,sc_type_arc_pos_const_perm,node, h2o);

        appendIntoAnswer(answer,h2o);
        appendIntoAnswer(answer,arc3_1);
        SC_ADDR_MAKE_EMPTY(arc3_1);

    }
    sc_iterator3_free(basics);//////////////////////////////////////////////////////////////////////////////////////////
    }





}





connect_answer_to_question(question, answer);

finish_question(question);
    return SC_RESULT_OK;
}

