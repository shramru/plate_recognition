#pragma once
#include <string>
#include <vector>
#include <utility>
#include "figure.h"

namespace cv
{
	class Mat;
}

// @todo: сделать документацию
// @todo: !!!!!!!!!!!!!если номер будет наклонным, то ширина будет не пропорциональная высоте (надо вводить косинусь угла наклона)!!!!!!!!!!!!!!!!!!!
// @todo: переделать мепинг символов к индексам массива, свитч лажа
// @todo: при распознавании символа, растянуть всю область, что бы убрать белый бордер, если он есть
// @todo: сделать перебор g_points_dublicate_first итераторами, а не индексами

// @todo: M520PX190.jpg - большой угол и слева шуруп, поэтому левая буква М не распознается

// найденный номер
struct found_number
{
	found_number()
		: m_number( std::string() )
		, m_weight( -1 )
	{
	}
	std::string m_number;		// номер
	int m_weight;			// вес
	std::vector< figure > m_figs;

	std::pair< std::string, int > to_pair() const
	{
		return std::make_pair( m_number, m_weight );
	}

	bool operator < ( const found_number& other ) const
	{
		const int cnp = count_not_parsed_syms();
		const int cnp_other = other.count_not_parsed_syms();
		if ( cnp != cnp_other )
		{
			return cnp > cnp_other;
		}
		else
		{
			return m_weight < other.m_weight;
		}
	}

	bool is_valid() const
	{
		return m_weight != -1 && !m_number.empty();
	}

	int count_not_parsed_syms() const
	{
		if ( m_number.empty() )
			return 100; // вообще ничего нет
		return count( m_number.begin(), m_number.end(), '?' );
	}
};


found_number read_number( const cv::Mat& image, int gray_step = 0 );
found_number read_number_by_level( const cv::Mat& image, int gray_level );
