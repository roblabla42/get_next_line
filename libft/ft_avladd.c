/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_avladd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlambert <rlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 16:42:47 by rlambert          #+#    #+#             */
/*   Updated: 2014/11/11 17:38:42 by rlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_avlupdateheight(t_avl *n)
{
	n->height = ft_max(ft_avlheight(n->left), ft_avlheight(n->right)) + 1;
}

static void		ft_avllrotate(t_avl **node)
{
	t_avl	*root;
	t_avl	*pivot;

	root = (*node);
	pivot = root->right;
	root->right = pivot->left;
	pivot->left = root;
	ft_avlupdateheight(root);
	ft_avlupdateheight(pivot);
	*node = pivot;
}

static void		ft_avlrrotate(t_avl **node)
{
	t_avl	*root;
	t_avl	*pivot;

	root = (*node);
	pivot = root->left;
	root->left = pivot->right;
	pivot->right = root;
	ft_avlupdateheight(root);
	ft_avlupdateheight(pivot);
	*node = pivot;
}

static int		ft_avlbalance(t_avl *n)
{
	if (n == NULL)
		return (0);
	else
		return (ft_avlheight(n->left) - ft_avlheight(n->right));
}

void			ft_avladd(t_avl **node, t_avl *avl)
{
	if (*node == NULL)
	{
		*node = avl;
		return;
	}
	if (avl->key < (*node)->key)
		ft_avladd(&(*node)->left, avl);
	else
		ft_avladd(&(*node)->right, avl);
	ft_avlupdateheight(*node);
	int balance = ft_avlbalance(*node);
	if (balance > 1 && avl->key < (*node)->left->key)
		ft_avlrrotate(node);
	else if (balance < -1 && avl->key > (*node)->right->key)
		ft_avllrotate(node);
	else if (balance > 1 && avl-> key > (*node)->left->key)
	{
		ft_avllrotate(&(*node)->left);
		ft_avlrrotate(node);
	}
	else if (balance < -1 && avl->key < (*node)->right->key)
	{
		ft_avlrrotate(&(*node)->right);
		ft_avllrotate(node);
	}
}
