#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include <fstream>
using std::fstream; using std::ifstream; using std::ofstream;
#include<string>
using std::string; using std::to_string;
#include<sstream>
#include<vector>
using std::vector;
#include<sstream>
using std::ostringstream; using std::ostream;
#include <algorithm>
using std::min_element; using std::max_element;
#include <cctype>
using std::tolower; using std::isspace;

#include "proj08-struct.h"


vector<long> split(const string &s){
	vector<long> r;
	long ele;
	std::istringstream k(s);
	while(k >> ele){
		r.push_back(ele);
	}
	return r;
}

Image::Image(string f_name){
	ifstream fp;
	fp.open(f_name);
	string x;
	vector<long> prop;
	while (getline(fp, x)) {
		if(x[0] == '#' || isalpha(x[0])){
			continue;
		} else if (width_== 0){
			std::istringstream iss(x);
			iss >> width_ >> height_;
		} else if(max_val_ ==0){
			std::istringstream iss(x);
			iss >> max_val_;
		} else{
			pixels_.push_back(split(x));
		}
	}
}

void Image::write_image (string f_name) const{
	
	ofstream output_file(f_name);
	output_file<<"P2\n";
	output_file << height_ << " " << width_ << endl;
	
	output_file << max_val_ << endl;

	for(int h = 0; h < height_; h++){
		for(int w = 0; w< width_; w++){
			output_file << pixels_[h][w] << " ";
		}
		output_file << endl;
	}
	output_file.close();
}

Image Image::convolve(vector<vector<long>> mask, long div, long whiten) const{
	Image new_image;
	
	vector<vector<long>> new_pixels;
	for(int h = 0; h < height_; h++){
		vector<long> n_temp_row;
		for(int w = 0; w< width_; w++){
			long pixel_total = 0;
			int mask_row = 0;
			for (int y=-1;y<2;y++){
				int mask_col = 0;
				for(int z =-1;z<2;z++){
					if((h+y >= 0 && h+y <height_)&& (w+z >= 0 && w+z <width_)){
						long temp_pixel = (pixels_[h+y][w+z] * mask[mask_row][mask_col]);
						pixel_total +=temp_pixel;
					}
					mask_col++;
				}
				mask_row++;
			}
			pixel_total += whiten;
			pixel_total /=div;
			if(pixel_total <0) pixel_total = 0;
			else if(pixel_total > 245) pixel_total = 245;
			n_temp_row.push_back(pixel_total);
		}
		new_pixels.push_back(n_temp_row);
	}
	new_image.pixels_ = new_pixels;
	new_image.width_ = width_;
	new_image.height_ = height_;
	new_image.max_val_ = max_val_;
	
	return new_image;
}

Image Image::sharpen() const{
	vector<vector<long>> sharpen_mask = {{0,-1,0},{-1,5,-1},{0,-1,0}};
	auto n_sharpen = convolve(sharpen_mask);
	return n_sharpen;
}

Image Image::edge_detect() const{
	vector<vector<long>> edge_detect_mask = {{0,1,0},{1,-4,1},{0,1,0}};
	auto n_edge_detect =convolve(edge_detect_mask,1,50);
	return n_edge_detect;
}

Image Image::blur() const{
	vector<vector<long>> blur_mask = {{1,1,1},{1,1,1},{1,1,1}};
	auto n_blur =convolve(blur_mask,9,0);
	return n_blur;
}

Image Image::emboss() const{
	vector<vector<long>> emboss_mask = {{-2,-1,0},{-1,1,1},{0,1,2}};
	auto n_emboss=convolve(emboss_mask);
	return n_emboss;
}

void Image::embed(const Image &secret){
	vector<vector<long>> new_pixels;
	for(int h = 0; h < height_; h++){
		vector<long> temp;
		for(int w = 0; w< width_; w++){
			if(secret.pixels_[h][w]==0){
				if(pixels_[h][w]%2!=0) pixels_[h][w] -= 1;
			} else {
				if(pixels_[h][w]%2==0){
					if(pixels_[h][w]==max_val_) pixels_[h][w]-=1;
					else pixels_[h][w]+=1;
				}
			}
		}
		new_pixels.push_back(temp);
	}
}

Image Image::extract(long max_value) const {
	Image extracted;
	
	extracted.height_ = height_;
	extracted.width_ = width_;
	extracted.max_val_ = max_value;
	
	vector<vector<long>> new_pixels;
	for(int h = 0; h < height_; h++){
		vector<long> temp;
		for(int w = 0; w< width_; w++){
			if(pixels_[h][w]%2==0) temp.push_back(0);
			else temp.push_back(max_value);
		}
		new_pixels.push_back(temp);
	}
	extracted.pixels_ = new_pixels;
	return extracted;
	
}

