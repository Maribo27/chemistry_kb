#include "compound_reaction.h"
#include "search_keynodes.h"
#include "search_utils.h"
#include "search.h"
#include "utils.h"
#include "stdio.h"


sc_result agent_compound_reaction(const sc_event *event, sc_addr arg)
{
    sc_addr question, answer;
    sc_iterator3 *it1;
    sc_bool sys_off = SC_TRUE;
    sc_addr substance;
    sc_addr nrel_inclusion;
    sc_addr nrel_count_of_inclusion;
    sc_addr number;
    sc_addr nrel_compound;
    sc_addr set_of_elements;
    sc_addr concept_binary_elements;
    sc_addr concept_nonmetals;

    sc_addr concept_bases;
    sc_addr concept_acidic_oxide;
    sc_addr concept_acid;
    sc_addr concept_amphoteric_oxide;
    sc_addr concept_basic_oxide;
    sc_addr concept_hydrogen_oxide;
    sc_addr concept_metals;


    set_of_elements = sc_memory_node_new(s_default_ctx, sc_type_const); //множество хим элементов вещества

    if (!sc_memory_get_arc_end(s_default_ctx, arg, &question))
        return SC_RESULT_ERROR_INVALID_PARAMS;

    if (sc_helper_check_arc(s_default_ctx, keynode_question_compound_reaction, question, sc_type_arc_pos_const_perm) == SC_FALSE)
        return SC_RESULT_ERROR_INVALID_TYPE;

    answer = create_answer_node();
    sc_helper_resolve_system_identifier(s_default_ctx, "concept_nonmetals", &concept_nonmetals);
    sc_helper_resolve_system_identifier(s_default_ctx, "concept_binary_elements", &concept_binary_elements);
    sc_helper_resolve_system_identifier(s_default_ctx, "nrel_compound", &nrel_compound);
    sc_helper_resolve_system_identifier(s_default_ctx, "nrel_inclusion", &nrel_inclusion);
    sc_helper_resolve_system_identifier(s_default_ctx, "nrel_count_of_inclusion", &nrel_count_of_inclusion);
    sc_helper_resolve_system_identifier(s_default_ctx, "number", &number);
    sc_helper_resolve_system_identifier(s_default_ctx, "concept_bases", &concept_bases);
    sc_helper_resolve_system_identifier(s_default_ctx, "concept_acidic_oxide", &concept_acidic_oxide);
    sc_helper_resolve_system_identifier(s_default_ctx, "concept_acid", &concept_acid);
    sc_helper_resolve_system_identifier(s_default_ctx, "concept_amphoteric_oxide", &concept_amphoteric_oxide);
    sc_helper_resolve_system_identifier(s_default_ctx, "concept_basic_oxide", &concept_basic_oxide);
    sc_helper_resolve_system_identifier(s_default_ctx, "concept_hydrogen_oxide", &concept_hydrogen_oxide);
    sc_helper_resolve_system_identifier(s_default_ctx, "concept_metals", &concept_metals);

    sc_addr nrel_valence;
    sc_helper_resolve_system_identifier(s_default_ctx, "nrel_valence", &nrel_valence);

    printf("Agent initiated!\n");

    /* нахожу дугу от задаваемого вопроса с узлом-связкой substance и добавляю в ответ*/
    it1 = sc_iterator3_f_a_a_new(s_default_ctx,
                                 question,
                                 sc_type_arc_pos_const_perm,
                                 0);
    if (sc_iterator3_next(it1) == SC_TRUE)
    {
        substance = sc_iterator3_value(it1, 2);
    }
    sc_iterator3_free(it1);//очищаю итератор



    appendIntoAnswer(answer, substance);
    /* исследую дуги исходящие от substance и добавляю в ответ*/
    sc_iterator3 *iter3, *iter3_2, *iter4;
    sc_iterator5 *iter5;
    sc_bool check = SC_TRUE;
    sc_bool pump = SC_FALSE;
    sc_addr temp_subst;
    int cnt = 0, val = 0;
    temp_subst = sc_memory_node_new(s_default_ctx, sc_type_const);

//printf("ono rabotaet (net)\n");

    iter3 = sc_iterator3_f_a_a_new(s_default_ctx,
                                   substance,
                                   sc_type_arc_pos_const_perm,
                                   0);
    while (sc_iterator3_next(iter3) == SC_TRUE)
    {
        //printf("ono rabotaet (net)\n");

        appendIntoAnswer(answer, sc_iterator3_value(iter3, 1));
        appendIntoAnswer(answer, sc_iterator3_value(iter3, 2));

        sc_addr subst = sc_iterator3_value(iter3, 2);

        iter5 = sc_iterator5_f_a_a_a_f_new(s_default_ctx,
                                           subst,
                                           sc_type_arc_common | sc_type_const,
                                           0,
                                           sc_type_arc_pos_const_perm,
                                           nrel_valence);
        if (sc_iterator5_next(iter5) == SC_TRUE)
            val = getInt(s_default_ctx, sc_iterator5_value(iter5, 2));
        sc_iterator5_free(iter5);
        if (val != 0) pump = SC_TRUE;

        //printf("%d\n", val);

        if (sc_helper_check_arc(s_default_ctx, concept_metals, subst, sc_type_arc_pos_const_perm) || sc_helper_check_arc(s_default_ctx, concept_nonmetals, subst, sc_type_arc_pos_const_perm))
            if (sc_helper_check_arc(s_default_ctx, set_of_elements, subst, sc_type_arc_pos_const_perm) == SC_FALSE)
            {
                cnt++;
                sc_memory_arc_new(s_default_ctx, sc_type_arc_pos_const_perm, set_of_elements, subst);
            }


        iter5 = sc_iterator5_f_a_a_a_f_new(s_default_ctx,
                                           subst,
                                           sc_type_arc_common | sc_type_const,
                                           0,
                                           sc_type_arc_pos_const_perm,
                                           nrel_inclusion);
        while (sc_iterator5_next(iter5) == SC_TRUE)
        {
           // printf("coc\n");
            sc_addr elem = sc_iterator5_value(iter5, 2);
            if (sc_helper_check_arc(s_default_ctx, set_of_elements, elem, sc_type_arc_pos_const_perm) == SC_FALSE)
            {
                cnt++;
                sc_memory_arc_new(s_default_ctx, sc_type_arc_pos_const_perm, set_of_elements, elem);
            }
        }
        sc_iterator5_free(iter5);
    }
    sc_iterator3_free(iter3);

    //printf("%d\n", cnt);




    iter3 = sc_iterator3_f_a_a_new(s_default_ctx,
                                   set_of_elements,
                                   sc_type_arc_pos_const_perm,
                                   0);
    while (sc_iterator3_next(iter3) == SC_TRUE)
    {
        sc_addr elem = sc_iterator3_value(iter3, 2);


        sc_iterator5 *it5 = sc_iterator5_a_a_f_a_f_new(s_default_ctx,
                                                       0,
                                                       sc_type_arc_common | sc_type_const,
                                                       elem,
                                                       sc_type_arc_pos_const_perm,
                                                       nrel_inclusion);

        while (sc_iterator5_next(it5) == SC_TRUE)
        {
            //printf("mmm....\n");

            sc_addr temp = sc_iterator5_value(it5, 0);
            printEl(s_default_ctx, temp);

            check = SC_TRUE;
            int cntx = 0, valx = 0;

            if (sc_helper_check_arc(s_default_ctx, concept_bases, temp, sc_type_arc_pos_const_perm) || sc_helper_check_arc(s_default_ctx, concept_amphoteric_oxide, temp, sc_type_arc_pos_const_perm)
                    || sc_helper_check_arc(s_default_ctx, concept_acidic_oxide, temp, sc_type_arc_pos_const_perm) || sc_helper_check_arc(s_default_ctx, concept_acid, temp, sc_type_arc_pos_const_perm)
                    || sc_helper_check_arc(s_default_ctx, concept_basic_oxide, temp, sc_type_arc_pos_const_perm) || sc_helper_check_arc(s_default_ctx, concept_hydrogen_oxide, temp, sc_type_arc_pos_const_perm))
            {
                sc_iterator5 *it5_2 = sc_iterator5_f_a_a_a_f_new(s_default_ctx,
                                                                 temp,
                                                                 sc_type_arc_common | sc_type_const,
                                                                 0,
                                                                 sc_type_arc_pos_const_perm,
                                                                 nrel_valence);
                if (sc_iterator5_next(it5_2) == SC_TRUE)
                    valx = getInt(s_default_ctx, sc_iterator5_value(it5_2, 2));
                sc_iterator5_free(it5_2);

                if (pump)
                    if (valx != val) check = SC_FALSE;
                    //printf("%d %d \n", val, valx);

                sc_iterator5 *itx = sc_iterator5_f_a_a_a_f_new(s_default_ctx,
                                                               temp,
                                                               sc_type_arc_common | sc_type_const,
                                                               0,
                                                               sc_type_arc_pos_const_perm,
                                                               nrel_inclusion);
                while (sc_iterator5_next(itx) == SC_TRUE)
                    cntx++;
//printf("%d %d\n", cnt,cntx);

                if (cnt != cntx) check = SC_FALSE;

                if (!sc_helper_check_arc(s_default_ctx, temp_subst, temp, sc_type_arc_pos_const_perm) & check)
                    sc_memory_arc_new(s_default_ctx, sc_type_arc_pos_const_perm, temp_subst, temp);
            }
        }
        sc_iterator5_free(it5);
    }
    sc_iterator3_free(iter3);


    iter3 = sc_iterator3_f_a_a_new(s_default_ctx,
                                   set_of_elements,
                                   sc_type_arc_pos_const_perm,
                                   0);
    while (sc_iterator3_next(iter3) == SC_TRUE)
    {
        sc_addr elemx = sc_iterator3_value(iter3, 2);
        iter3_2 = sc_iterator3_f_a_a_new(s_default_ctx,
                                         temp_subst,
                                         sc_type_arc_pos_const_perm,
                                         0);
        while (sc_iterator3_next(iter3_2) == SC_TRUE)
        {
            iter5 = sc_iterator5_f_a_f_a_f_new(s_default_ctx,
                                               sc_iterator3_value(iter3_2, 2),
                                               sc_type_arc_common | sc_type_const,
                                               elemx,
                                               sc_type_arc_pos_const_perm,
                                               nrel_inclusion);

            if (sc_iterator5_next(iter5) == SC_FALSE)
            {
                sc_addr arc = sc_iterator3_value(iter3_2, 1);
                sc_memory_element_free(s_default_ctx, arc);
            }
            sc_iterator5_free(iter5);

        }
        sc_iterator3_free(iter3_2);
    }

    sc_iterator3_free(iter3);



    iter3_2 = sc_iterator3_f_a_a_new(s_default_ctx,
                                     temp_subst,
                                     sc_type_arc_pos_const_perm,
                                     0);


    while (sc_iterator3_next(iter3_2) == SC_TRUE)
    {
        sc_addr sub = sc_iterator3_value(iter3_2, 2);
        sc_addr arc1 = sc_memory_arc_new(s_default_ctx, sc_type_arc_common | sc_type_const, substance, sub);
        sc_addr arc2 = sc_memory_arc_new(s_default_ctx, sc_type_arc_pos_const_perm, nrel_compound, arc1);
        appendIntoAnswer(answer, sub);
        appendIntoAnswer(answer, arc1);
        appendIntoAnswer(answer, nrel_compound);
        appendIntoAnswer(answer, arc2);
    }
    sc_iterator3_free(iter3_2);

    connect_answer_to_question(question, answer);

    finish_question(question);
    return SC_RESULT_OK;
}
